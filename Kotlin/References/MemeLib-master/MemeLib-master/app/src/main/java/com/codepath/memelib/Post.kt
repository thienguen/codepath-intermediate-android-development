package com.codepath.memelib

import com.parse.ParseClassName
import com.parse.ParseFile
import com.parse.ParseObject
import com.parse.ParseUser

@ParseClassName("Post")

//description : string, image : file, user : user
class Post : ParseObject() {

    fun getDescription() : String? {
        return getString(KEY_DESCRIPTION)
    }

    fun setDescription(description : String) {
        put(KEY_DESCRIPTION, description)
    }

    fun getImage() : ParseFile?{
        return getParseFile(KEY_IMAGE)
    }

    fun setImage(parseFile: ParseFile) {
        put(KEY_IMAGE, parseFile)
    }

    fun getUser() : ParseUser? {
        return getParseUser(KEY_USER)
    }

    fun setUser(user : ParseUser) {
        put(KEY_USER, user)
    }

    fun getID() : String? {
        return getString(KEY_ID)
    }

    companion object {
        const val KEY_DESCRIPTION = "caption"
        const val KEY_IMAGE = "image"
        const val KEY_USER = "author"
        const val KEY_ID = "objectId"
    }
}