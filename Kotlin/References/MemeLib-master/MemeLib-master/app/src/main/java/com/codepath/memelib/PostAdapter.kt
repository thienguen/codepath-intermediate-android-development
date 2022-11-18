package com.codepath.memelib

import android.content.Context
import android.content.Intent
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.core.graphics.drawable.DrawableCompat
import androidx.fragment.app.FragmentActivity
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide
import com.codepath.memelib.dialogs.feedfragment.AddToCollectionDialog
import com.codepath.memelib.fragments.ModifyFragment
import com.parse.Parse.getApplicationContext
import com.parse.ParseException
import com.parse.ParseQuery
import com.parse.ParseUser


class PostAdapter(var context: Context, val posts: List<Post>)
    : RecyclerView.Adapter<PostAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PostAdapter.ViewHolder {
        // specify layout file to use for this item
        val view = LayoutInflater.from(context).inflate(R.layout.item_post, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: PostAdapter.ViewHolder, position: Int) {
        val post = posts.get(position)
        holder.bind(post)
    }

    override fun getItemCount(): Int {
        return posts.size
    }

    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView){
        val tvUsername: TextView
        val tvDescription: TextView
        val ivImage: ImageView
        val tvTimeCreated: TextView
        // buttons for optional stories
        val ivFavorite: ImageView
        val ivShareButton: ImageView
        val ivEdit: ImageView
        val ivDelete: ImageView
        val ivAddToCollection: ImageView

        init {
            tvUsername = itemView.findViewById(R.id.tvUsername)
            tvDescription = itemView.findViewById(R.id.tvDescription)
            ivImage = itemView.findViewById(R.id.ivImage)
            tvTimeCreated = itemView.findViewById(R.id.tvTimeCreated)
            ivFavorite = itemView.findViewById(R.id.ivFavorite)
            ivShareButton = itemView.findViewById(R.id.ivShare)
            ivEdit = itemView.findViewById(R.id.ivEdit)
            ivDelete = itemView.findViewById(R.id.ivDelete)
            ivAddToCollection = itemView.findViewById(R.id.ivAddToCollection)
        }

        fun bind(post: Post) {
            tvDescription.text = post.getDescription()
            tvUsername.text = "@" + post.getUser()?.username
            tvTimeCreated.text = post.createdAt.toString()
            if (!post.getUser()?.objectId.equals(ParseUser.getCurrentUser().objectId)) {
//                Log.i("PostAdapter", post.getUser()?.get("objectId").toString())
//                Log.i("PostAdapter", ParseUser.getCurrentUser().get("objectId").toString())
                ivEdit.visibility = View.INVISIBLE
                ivDelete.visibility = View.INVISIBLE
            } else {
                ivEdit.isClickable = true
                ivEdit.setOnClickListener {
                    editPost(post)
                }
                ivDelete.isClickable = true
                ivDelete.setOnClickListener {

                    deletePost(post)
                }
            }

            // Populate image
            Glide.with(itemView.context)
                .load(post.getImage()?.url)
                .fitCenter() // scale to fit entire image within ImageView
                .into(ivImage)

            //adding to collection attempt
            ivFavorite.setOnClickListener { view: View? ->

                if (ParseUser.getCurrentUser().getJSONArray("collections")?.getJSONObject(1)?.has(post.getID()) == true) {
                    DrawableCompat.setTint(ivFavorite.drawable, ContextCompat.getColor(itemView.context, R.color.defaultcolor))
                    ParseUser.getCurrentUser().getJSONArray("collections")?.getJSONObject(1)?.remove(post.getID())
                }
                else {
                    DrawableCompat.setTint(ivFavorite.drawable, ContextCompat.getColor(itemView.context, R.color.red))
                    ParseUser.getCurrentUser().getJSONArray("collections")?.getJSONObject(1)
                        ?.put("post", post)
                }
            }

            ivAddToCollection.setOnClickListener { view: View? ->
                //TODO
                val addToCollectionDialog = AddToCollectionDialog()
                val fragmentManager = (view?.getContext() as FragmentActivity).supportFragmentManager
                addToCollectionDialog.show(fragmentManager, "addToCollectionDialog")
            }

            ivShareButton.setOnClickListener { view: View? ->
                //todo share on other apps optional
                val intent = Intent(getApplicationContext(), view_post::class.java)
                intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
                intent.putExtra("POST", post)
                getApplicationContext().startActivity(intent)
            }
        }

        private fun editPost(post: Post) {
            val activity = itemView.context as AppCompatActivity
            val fragment = ModifyFragment()
            val bundle = Bundle()
            bundle.putParcelable("post", post)
            fragment.arguments = bundle
            val fm = activity.supportFragmentManager
            fm.beginTransaction().replace(R.id.flContainer, fragment).addToBackStack(null).commit()
        }

        private fun deletePost(post: Post) {
            val query: ParseQuery<Post> = ParseQuery.getQuery(Post::class.java)
            query.getInBackground(
                post.objectId
            ) { post: Post, e: ParseException? ->
                if (e == null) {
                    // Deletes the fetched ParseObject from the database
                    post.deleteInBackground { e2: ParseException? ->
                        if (e2 == null) {
                            Toast.makeText(itemView.context,
                                "Delete Successful. Please refresh to see!",
                                Toast.LENGTH_SHORT)
                                .show()
                        } else {
                            //Something went wrong while deleting the Object
                            Toast.makeText(itemView.context, "Error: " + e2.message, Toast.LENGTH_SHORT)
                                .show()
                        }
                    }
                } else {
                    //Something went wrong while retrieving the Object
                    Toast.makeText(itemView.context, "Error: " + e.message, Toast.LENGTH_SHORT).show()
                }
            }
        }
    }
}