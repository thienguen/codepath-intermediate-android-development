package com.codepath.memelib

import android.util.Log
import com.codepath.memelib.fragments.FeedFragment
import com.parse.*
import org.json.JSONArray
import org.json.JSONObject

@ParseClassName("Collections")

class Collections : ParseObject() {

    fun getDescription() : String? {
        return getString(KEY_DESCRIPTION)
    }

    fun setDescription(description : String) {
        put(KEY_DESCRIPTION, description)
    }

    fun getName() : String?{
        return getString(KEY_NAME)
    }

    fun setName(name: String) {
        put(KEY_NAME, name)
    }

    fun getUser() : ParseUser? {
        return getParseUser(KEY_USER)
    }

    fun setUser(user : ParseUser) {
        put(KEY_USER, user)
    }

    fun getCollection() : ArrayList<Post> {
        var postsJson : JSONArray? = getJSONArray(KEY_COLLECTION)
        var posts : ArrayList<Post> = ArrayList()
        if (postsJson != null && postsJson.length() > 0) {
            for (i in 0..postsJson.length()) {
                val objectId = postsJson.getString(i)
                val query: ParseQuery<Post> = ParseQuery.getQuery(Post::class.java)

                query.getInBackground(objectId)
                posts.add(query.first)
            }
        }
        return posts
    }

    fun setCollection(collection : List<Post>) {
        put(KEY_COLLECTION, collection)
    }

    fun getID() : String? {
        return getString(KEY_ID)
    }

    companion object {
        const val KEY_DESCRIPTION = "description"
        const val KEY_NAME = "name"
        const val KEY_USER = "user"
        const val KEY_ID = "objectId"
        const val KEY_COLLECTION = "collection" //array stored with posts
    }
}