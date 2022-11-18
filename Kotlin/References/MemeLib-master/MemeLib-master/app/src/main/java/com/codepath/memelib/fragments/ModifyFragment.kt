package com.codepath.memelib.fragments

import android.content.Intent
import android.graphics.Bitmap
import android.graphics.ImageDecoder
import android.media.MediaPlayer
import android.net.Uri
import android.os.Build
import android.os.Bundle
import android.os.Environment
import android.provider.MediaStore
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.EditText
import android.widget.ImageView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.codepath.memelib.MainActivity
import com.codepath.memelib.Post
import com.codepath.memelib.R
import com.codepath.memelib.SoundClick
import com.parse.ParseFile
import com.parse.ParseQuery
import com.parse.ParseUser
import java.io.File
import java.io.FileOutputStream
import java.io.IOException
import java.io.InputStream
import java.text.SimpleDateFormat
import java.util.*


/**
 * A simple [Fragment] subclass.
 * Use the [ModifyFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class ModifyFragment(override var mp: MediaPlayer? = null) : Fragment(),SoundClick{

    val PICK_PHOTO_CODE = 1046;
    val photoFileName = "photo.jpg"
    var photoFile: File? = null

    lateinit var ivPreview: ImageView
    lateinit var post: Post

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val id: String? = savedInstanceState?.getString("id")
        val query: ParseQuery<Post> = ParseQuery.getQuery(Post::class.java)
        val bundle = arguments
        post = bundle!!.getParcelable<Post>("post")!!
        return inflater.inflate(R.layout.fragment_compose, container, false)
    }

    override fun startSound() {
        super.startSound()
        if (mp == null) {
            mp = MediaPlayer.create(requireContext(), R.raw.sample)
        }
        mp?.start()
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        ivPreview = view.findViewById(R.id.imageView)

        view.findViewById<Button>(R.id.btnSubmit).setOnClickListener {
            // send post to server without an image
            // Get the description that they have inputted
            startSound()
            val description = view.findViewById<EditText>(R.id.description).text.toString()
            val user = ParseUser.getCurrentUser()
            if (photoFile != null) {
                submitPost(description, user, photoFile!!)
            } else {
                Toast.makeText(requireContext(), "Missing Photo", Toast.LENGTH_SHORT).show()
                submitPost(description, user, null)
            }
        }

        view.findViewById<Button>(R.id.btnPicture).setOnClickListener{
            // Launch camera to let user choose picture
            startSound()
            onPickPhoto()
        }
    }

    // Send a post to our Parse server
    private fun submitPost(description: String, user: ParseUser, file: File?) {
        // Create the Post object
        post.setDescription(description)
        post.setUser(user)
        if (file != null) {
            post.setImage(ParseFile(file))
        }
        post.saveInBackground{ e ->
            if (e != null) {
                // Something went wrong
                Log.e(MainActivity.TAG, "Error while saving post")
                e.printStackTrace()
                // show a toast to tell user something went wrong with saving post
                Toast.makeText(requireContext(), "Error saving post", Toast.LENGTH_SHORT).show()
            } else {
                Log.i(MainActivity.TAG, "Successfully saved post")
                // Resetting the EditText field to be empty
                // Reset the ImageView to empty
                view?.findViewById<EditText>(R.id.description)?.text?.clear()
                ivPreview.setImageBitmap(null)
            }
        }
    }

    fun onPickPhoto() {
        val intent = Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI)
        photoFile = getPhotoFileUri(photoFileName)
//        if (intent.resolveActivity(requireContext().packageManager) != null) {
        Toast.makeText(requireContext(), "PickPhoto start", Toast.LENGTH_SHORT).show()
        startActivityForResult(intent, PICK_PHOTO_CODE);
//        }
    }

    // Returns the File for a photo stored on disk given the fileName
    fun getPhotoFileUri(fileName: String): File {
        // Get safe storage directory for photos
        // Use `getExternalFilesDir` on Context to access package-specific directories.
        // This way, we don't need to request external read/write runtime permissions.
        val mediaStorageDir =
            File(requireContext().getExternalFilesDir(Environment.DIRECTORY_PICTURES), MainActivity.TAG)

        // Create the storage directory if it does not exist
        if (!mediaStorageDir.exists() && !mediaStorageDir.mkdirs()) {
            Log.d(MainActivity.TAG, "failed to create directory")
        }

        // Return the file target for the photo based on filename
        return File(mediaStorageDir.path + File.separator + fileName)
    }

    fun loadFromUri(photoUri: Uri): Bitmap? {
        val image: Bitmap?

        if (Build.VERSION.SDK_INT > 27) {
            val source: ImageDecoder.Source = ImageDecoder.createSource(requireContext().contentResolver, photoUri)
            image = ImageDecoder.decodeBitmap(source)
        } else {
            image = MediaStore.Images.Media.getBitmap(requireContext().contentResolver, photoUri)
        }

        if (image == null) {
            Log.e(TAG, "Can't load photo from gallery")
            Toast.makeText(requireContext(), "Can't load photo from gallery", Toast.LENGTH_SHORT)
                .show()
        }
        return image
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if ( data != null && requestCode == PICK_PHOTO_CODE) {
            if (resultCode == AppCompatActivity.RESULT_OK) {
                val image: Bitmap? = data.data?.let { loadFromUri(it) }
                ivPreview.setImageBitmap(image)
                try {
                    photoFile = createImageFile()
                } catch (ex: IOException) {
                    Log.d(TAG, "Error occurred while creating the file")
                }

                val inputStream: InputStream? =
                    data.data?.let { requireActivity().contentResolver.openInputStream(it) }
                val fileOutputStream = FileOutputStream(photoFile)

                copyStream(inputStream, fileOutputStream)
                fileOutputStream.close()
                inputStream?.close()

            }
        } else {
            Toast.makeText(requireContext(), "Picture wasn't chosen!", Toast.LENGTH_SHORT).show()
        }
    }

    private fun copyStream(input: InputStream?, output: FileOutputStream) {
        val buffer = ByteArray(1024)
        var bytesRead: Int
        if (input != null) {
            while (input.read(buffer).also { bytesRead = it } != -1) {
                output.write(buffer, 0, bytesRead)
            }
        }
    }

    private fun createImageFile(): File? {
        // Create an image file name
        // Create an image file name
        val timeStamp: String = SimpleDateFormat("yyyyMMdd_HHmmss").format(Date())
        val imageFileName = "JPEG_" + timeStamp + "_"
        val storageDir = requireActivity().getExternalFilesDir(Environment.DIRECTORY_PICTURES)
        val image = File.createTempFile(
            imageFileName,  /* prefix */
            ".jpg",  /* suffix */
            storageDir /* directory */
        )

        return image
    }

    companion object {
        const val TAG = "Compose Fragment"
    }
}