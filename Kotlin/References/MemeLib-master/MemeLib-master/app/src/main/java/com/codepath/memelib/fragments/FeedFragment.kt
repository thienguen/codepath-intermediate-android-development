package com.codepath.memelib.fragments

import android.content.Intent
import android.graphics.drawable.BitmapDrawable
import android.media.MediaPlayer
import android.net.Uri
import android.os.Bundle
import android.provider.MediaStore
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import androidx.fragment.app.Fragment
import androidx.fragment.app.FragmentActivity
import androidx.recyclerview.widget.DividerItemDecoration
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout
import com.codepath.memelib.*
import com.codepath.memelib.dialogs.feedfragment.CreateCollectionDialog
import com.codepath.memelib.dialogs.feedfragment.EditCollectionDialog
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.parse.ParseQuery
import com.parse.ParseUser

open class FeedFragment(override var mp: MediaPlayer? = null) : Fragment(), SoundClick{

    lateinit var logoutbtn: Button
    lateinit var postRecyclerView: RecyclerView
    lateinit var adapter: PostAdapter
    lateinit var swipeContainer: SwipeRefreshLayout
    var allPosts: MutableList<Post> = mutableListOf()

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_feed, container, false)
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

        swipeContainer = view.findViewById(R.id.swipeContainer)
        // Setup refresh listener which triggers new data loading

        swipeContainer.setOnRefreshListener {
            // Your code to refresh the list here.
            // Make sure you call swipeContainer.setRefreshing(false)
            // once the network request has completed successfully.
            queryPosts()
            swipeContainer.isRefreshing = false
        }

        // Configure the refreshing colors
        swipeContainer.setColorSchemeResources(android.R.color.holo_blue_bright,
            android.R.color.holo_green_light,
            android.R.color.holo_orange_light,
            android.R.color.holo_red_light);

        postRecyclerView = view.findViewById(R.id.postRecyclerView)

        val dividerItemDecoration = DividerItemDecoration(requireContext(), DividerItemDecoration.VERTICAL)
        postRecyclerView.addItemDecoration(dividerItemDecoration)

        // populate recyclerview:
        // create layout for each row in list
        // create data source for each row
        // create adapter that will bridge data and row layout (post adapter class)
        // set adapter on recyclerview
        adapter = PostAdapter(requireContext(), allPosts)
        postRecyclerView.adapter = adapter
        // set layout manager on recyclerview
        postRecyclerView.layoutManager = LinearLayoutManager(requireContext())

        queryPosts()

        logoutbtn = view.findViewById<Button>(R.id.btnLogout)
        logoutbtn.isEnabled = ParseUser.getCurrentUser() != null

        logoutbtn.setOnClickListener {
            //Launch the camera for the user to take picture
            startSound()
            ParseUser.logOut()
            goToLoginActivity()
        }

    }

    private fun goToLoginActivity() {
        val intent = Intent(this.requireContext(), LoginActivity::class.java)
        startActivity(intent)
        //finish()             //closes the MainActivity, avoiding going back to main page on clicking back
    }

    // query for all posts in our server
    open fun queryPosts() {

        // SwipeRefresh: Clear posts first
        allPosts.clear()

        // SwipeRefresh: Populate again
        //specify which class to query
        // Specify which class to query
        val query: ParseQuery<Post> = ParseQuery.getQuery(Post::class.java)
        query.include(Post.KEY_USER)

        //return posts in descending order based on posted time
        query.addDescendingOrder("createdAt")

        query.findInBackground { posts, e ->
            if (e != null) {
                Log.e(TAG, "Error fetching posts")
            } else {
                if (posts != null) {
                    for (post in posts) {
                        Log.i(TAG, "Post: " + post.getDescription() + " , username: " + post.getUser()?.username)
                    }
                    allPosts.addAll(posts)
                    adapter.notifyDataSetChanged()
                }
            }
        }
    }

    companion object {
        const val TAG = "FeedFragment"
    }
}