package com.codepath.memelib.dialogs.feedfragment

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import android.widget.Toast.LENGTH_SHORT
import androidx.fragment.app.DialogFragment
import com.codepath.memelib.Collections
import com.codepath.memelib.R
import com.codepath.memelib.fragments.ProfileFragment
import com.parse.ParseQuery
import com.parse.ParseUser


class AddToCollectionDialog : DialogFragment()  {

    var allCollections: MutableList<Collections> = mutableListOf()

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.add_to_collection_dialog, container)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val query: ParseQuery<Collections> = ParseQuery.getQuery(Collections::class.java)
        query.include(Collections.KEY_USER)
        //only return posts from current signed in user
        query.whereEqualTo(Collections.KEY_USER, ParseUser.getCurrentUser())
        //return posts in descending order based on posted time
        query.addDescendingOrder("createdAt")

        query.findInBackground { collections, e ->
            if (e != null) {
                Log.e(ProfileFragment.TAG, "Error fetching posts")
            } else {
                if (collections != null) {
                    for (collection in collections) {
                        allCollections.add(collection)
                        Log.i(
                            ProfileFragment.TAG,
                            "Post: " + collection.getName() + " , username: " + collection.getUser()?.username
                        )
                    }
                }
            }
        }

        val myListView : ListView = view.findViewById(R.id.collectionList)
        myListView.adapter = ArrayAdapter<Collections>(requireActivity(), android.R.layout.simple_list_item_1, allCollections)

        myListView.setOnItemClickListener {
                adapterView,
                view,
                position,
                l -> Toast.makeText(activity, allCollections[position].getName(), LENGTH_SHORT).show()
        }

        val title = arguments?.getString("title", "Add to collection")
        dialog!!.setTitle(title)
        // Show soft keyboard automatically and request focus to field
        // Show soft keyboard automatically and request focus to field
        myListView.requestFocus()

    }
}