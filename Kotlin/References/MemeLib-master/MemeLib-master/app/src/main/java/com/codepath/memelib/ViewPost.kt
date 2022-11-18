package com.codepath.memelib

import android.content.Intent
import android.graphics.drawable.BitmapDrawable
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.provider.MediaStore
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import com.bumptech.glide.Glide
import org.w3c.dom.Text

class view_post : AppCompatActivity() {




    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_view_post)

        val post : Post? = getIntent().getParcelableExtra("POST")

        val returnButton : ImageButton = findViewById(R.id.returnBtn)
        val img : ImageView  = findViewById(R.id.ivImage)
        val description : TextView  = findViewById(R.id.tvDescription)
        val timecreated : TextView  = findViewById(R.id.tvTimeCreated)
        val tags : TextView  = findViewById(R.id.tvTags)
        val shareBtn : ImageView  = findViewById(R.id.ivShare)
        val favBtn : ImageView  = findViewById(R.id.ivFavorite)
        val bookmarkBtn : ImageView  = findViewById(R.id.ivAddToCollection)
        val editBtn : ImageView  = findViewById(R.id.ivEdit)
        val deleteBtn : ImageView  = findViewById(R.id.ivDelete)

        if (post != null) {
            Glide.with(this)
                .load(post.getImage()?.url)
                .fitCenter() // scale to fit entire image within ImageView
                .into(img)
        }

        if (post != null) {
            description.text = post.getDescription()
            timecreated.text = post.createdAt.toString()
            tags.text = "#ilovememes"
        }

            val bitmapDrawable = img.drawable as BitmapDrawable
            val bitmap = bitmapDrawable.bitmap
            val bitmapPath = MediaStore.Images.Media.insertImage(contentResolver, bitmap, "Share meme with friends", null)
            val bitmapUri = Uri.parse(bitmapPath)

            val shareIntent: Intent = Intent().apply {
                action = Intent.ACTION_SEND
                putExtra(Intent.EXTRA_STREAM, bitmapUri)
                type = "image/jpeg"
            }
            startActivity(Intent.createChooser(shareIntent, "Share memes"))

        returnButton.setOnClickListener {
            finish() //go back
        }
    }
}