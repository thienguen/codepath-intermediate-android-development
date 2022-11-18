package com.codepath.memelib.fragments

import android.content.Intent
import android.media.MediaPlayer
import android.os.Bundle
import android.util.Log
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
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

open class ProfileFragment(override var mp: MediaPlayer? = null) : Fragment(), SoundClick{

    lateinit var logoutbtn: Button
    var allCollections: MutableList<Collections> = mutableListOf()
    lateinit var adapter: CollectionAdapter
    lateinit var swipeContainer: SwipeRefreshLayout
    lateinit var collectionsRecyclerView: RecyclerView
    lateinit var addCollectionBtn : FloatingActionButton

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_profile, container, false)
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

        addCollectionBtn = view.findViewById(R.id.AddCollectionBtn)

        addCollectionBtn.setOnClickListener {
            val CreateCollectionDialog = CreateCollectionDialog()
            val fragmentManager = (view.getContext() as FragmentActivity).supportFragmentManager
            CreateCollectionDialog.show(fragmentManager, "CreateCollectionDialog")
        }

        swipeContainer = view.findViewById(R.id.swipeContainer)

        swipeContainer.setOnRefreshListener {
            // Your code to refresh the list here.
            // Make sure you call swipeContainer.setRefreshing(false)
            // once the network request has completed successfully.
            queryCollections()
            swipeContainer.isRefreshing = false
        }

        // Configure the refreshing colors
        swipeContainer.setColorSchemeResources(android.R.color.holo_blue_bright,
            android.R.color.holo_green_light,
            android.R.color.holo_orange_light,
            android.R.color.holo_red_light);

        collectionsRecyclerView = view.findViewById(R.id.rvCollections)

        val dividerItemDecoration = DividerItemDecoration(requireContext(), DividerItemDecoration.VERTICAL)
        collectionsRecyclerView.addItemDecoration(dividerItemDecoration)

        adapter = CollectionAdapter(requireContext(), allCollections)
        collectionsRecyclerView.adapter = adapter
        // set layout manager on recyclerview
        collectionsRecyclerView.layoutManager = LinearLayoutManager(requireContext())

        queryCollections()

//        var fragmentToShow: Fragment? = MyPostsFragment()
//
//        if (fragmentToShow != null) {
//            fragmentManager?.beginTransaction()?.replace(R.id.flContainer, fragmentToShow)?.commit()
//        }
//        Toast.makeText(requireContext(), "My Posts", Toast.LENGTH_SHORT).show()

        logoutbtn = view.findViewById<Button>(R.id.btnLogout)
        logoutbtn.isEnabled = ParseUser.getCurrentUser() != null

        logoutbtn.setOnClickListener {
            //Launch the camera for the user to take picture
            startSound()
            ParseUser.logOut()
            goToLoginActivity()
        }
    }

    open fun queryCollections() {
        // SwipeRefresh: Clear posts first
        allCollections.clear()

        // SwipeRefresh: Populate again
        //specify which class to query
        // Specify which class to query
        val query: ParseQuery<Collections> = ParseQuery.getQuery(Collections::class.java)
        query.include(Collections.KEY_USER)
        //only return posts from current signed in user
        query.whereEqualTo(Collections.KEY_USER, ParseUser.getCurrentUser())
        //return posts in descending order based on posted time
        query.addDescendingOrder("createdAt")

        query.findInBackground { collections, e ->
            if (e != null) {
                Log.e(TAG, "Error fetching posts")
            } else {
                if (collections != null) {
                    for (collection in collections) {
                            allCollections.add(collection)
                        Log.i(
                            TAG,
                            "Post: " + collection.getName() + " , username: " + collection.getUser()?.username
                        )
                    }
                    adapter.notifyDataSetChanged()
                }
            }
        }
    }


    private fun goToLoginActivity() {
        val intent = Intent(this.requireContext(), LoginActivity::class.java)
        startActivity(intent)
        //finish()             //closes the MainActivity, avoiding going back to main page on clicking back
    }

    companion object {
        const val TAG : String = "ProfileFragment"
    }
}