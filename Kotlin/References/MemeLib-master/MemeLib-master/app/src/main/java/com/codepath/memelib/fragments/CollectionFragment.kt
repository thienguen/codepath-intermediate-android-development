package com.codepath.memelib.fragments

import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.codepath.memelib.Post
import com.codepath.memelib.R
import com.parse.ParseQuery
import com.parse.ParseUser

/**
 * A simple [Fragment] subclass.
 * Use the [CollectionFragment.newInstance] factory method to
 * create an instance of this fragment.
 */
class CollectionFragment : FeedFragment() {

    override fun queryPosts() {
        // SwipeRefresh: Clear posts first
        allPosts.clear()

        val bundle = arguments
        if (bundle != null) {
            val collectionPosts: ArrayList<Post> =
                bundle.getParcelableArrayList<Post>("posts") as ArrayList<Post>
            for (post in collectionPosts) {
                allPosts.add(post)
            }
        }
        adapter.notifyDataSetChanged()
    }
}