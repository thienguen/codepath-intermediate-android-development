package com.codepath.memelib

import android.content.Context
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.codepath.memelib.fragments.CollectionFragment
import com.codepath.memelib.fragments.FeedFragment
import com.codepath.memelib.fragments.MyPostsFragment
import com.parse.ParseQuery

class CollectionAdapter(val context: Context, private val collections: List<Collections>)
    : RecyclerView.Adapter<CollectionAdapter.ViewHolder>() {


    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val tvCollectionName : TextView = itemView.findViewById(R.id.tvCollectionName)
        private val deleteButton : ImageView = itemView.findViewById(R.id.deleteButton)
        var allCollections: MutableList<Collections> = mutableListOf()

        fun bind(collection: Collections, position: Int) {
            queryCollections()
            if (position == 0) {
                tvCollectionName.setText("My Posts")
            } else {
                try {
                    tvCollectionName.setText(allCollections.get(position - 1).getName())
                } catch (e: IndexOutOfBoundsException) {
                    tvCollectionName.setText((position - 1).toString())
                }
            }

            itemView.setOnClickListener {
                if (position == 0) {
                    val activity = itemView.context as AppCompatActivity
                    val fragment = MyPostsFragment()
                    val fm = activity.supportFragmentManager
                    fm.beginTransaction().replace(R.id.flContainer, fragment).addToBackStack(null)
                        .commit()
                } else {
                    val activity = itemView.context as AppCompatActivity
                    val fragment = CollectionFragment()
                    val fm = activity.supportFragmentManager
                    val bundle = Bundle()
                    val posts: ArrayList<Post> = allCollections.get(position - 1).getCollection()
                    bundle.putParcelableArrayList("posts", posts)
                    fm.beginTransaction().replace(R.id.flContainer, fragment).addToBackStack(null)
                        .commit()
                }
            }
        }

        private fun queryCollections() {
            allCollections.clear()

            val query: ParseQuery<Collections> = ParseQuery.getQuery(Collections::class.java)
            query.include(Collections.KEY_USER)

            //return posts in descending order based on posted time
            query.addDescendingOrder("createdAt")

            query.findInBackground { collections, e ->
                if (e != null) {
                    Log.e(FeedFragment.TAG, "Error fetching posts")
                } else {
                    if (collections != null) {
                        for (collection in collections) {
                            Log.i(FeedFragment.TAG, "Collection: " + collection.getName() + " , username: " + collection.getUser()?.username)
                        }
                        allCollections.addAll(collections)
                    }
                }
            }
        }

        private fun deleteCollection(collection: Collections) {
            openDialog()
        }

        private fun openDialog() {
//            val removeCollectionDialog = RemoveCollectionDialog()
//            removeCollectionDialog.show(getSupportFragmentManager(), "deleteContactDialog")
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): CollectionAdapter.ViewHolder {
        val view = LayoutInflater.from(context).inflate(R.layout.item_collection, parent, false)
        return CollectionAdapter.ViewHolder(view)
    }

    override fun onBindViewHolder(holder: CollectionAdapter.ViewHolder, position: Int) {
        val collection = collections.get(position)
        holder.bind(collection, position)
    }

    override fun getItemCount(): Int {
        return collections.size
    }
}