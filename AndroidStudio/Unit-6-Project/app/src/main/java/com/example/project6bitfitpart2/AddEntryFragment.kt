package com.example.project6bitfitpart2

import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.view.inputmethod.InputMethodManager
import android.widget.Button
import android.widget.EditText
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch

class AddEntryFragment : Fragment() {

    private lateinit var itemNameEditText: EditText
    private lateinit var itemCalEditText: EditText
    private lateinit var itemRecordButton: Button

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        fun closeKeyBoard() {
            val currentFocus = activity?.currentFocus
            if (currentFocus != null) {
                val imm =
                    activity?.getSystemService(Context.INPUT_METHOD_SERVICE) as InputMethodManager
                imm.hideSoftInputFromWindow(view.windowToken, 0)
            }
        }

        itemRecordButton.setOnClickListener {
            val name = itemNameEditText.text.toString()
            val cal = itemCalEditText.text.toString()

            if (name.isNotEmpty() && cal.isNotEmpty()) {
                closeKeyBoard()
                val newItem = BitFitItem(name, cal)
                newItem.let { item ->
                    lifecycleScope.launch(Dispatchers.IO) {
                        (activity?.application as BitFitApplication).db.bitfitDao().insert(
                            BitFitEntity(
                                itemName = item.itemName,
                                calories = item.calories
                            )
                        )
                    }
                }

                itemNameEditText.text.clear()
                itemCalEditText.text.clear()
            }
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?,
    ): View? {
        val view = inflater.inflate(R.layout.fragment_add_entry, container, false)
        itemNameEditText = view.findViewById(R.id.ItemNameEditText)
        itemCalEditText = view.findViewById(R.id.ItemCaloriesEditText)
        itemRecordButton = view.findViewById(R.id.RecordItemButton)

        return view
    }

}