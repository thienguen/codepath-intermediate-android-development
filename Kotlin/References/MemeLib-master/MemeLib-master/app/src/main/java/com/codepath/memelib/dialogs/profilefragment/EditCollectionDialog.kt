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


class EditCollectionDialog : DialogFragment()  {

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



        val title = arguments?.getString("title", "Edit collection")
        dialog!!.setTitle(title)

    }
}