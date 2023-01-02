package com.example.simplewishlist

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.lifecycle.ViewModelProvider
import com.example.simplewishlist.databinding.FragmentNewWishListBinding
import com.google.android.material.bottomsheet.BottomSheetDialogFragment

class NewWishList(var wishItem : WishListItem?) : BottomSheetDialogFragment()
{
    private lateinit var binding : FragmentNewWishListBinding
    private lateinit var wishListModel : WishListModel

    override fun onViewCreated(view: View, savedInstanceState: Bundle?)
    {
        // Similartiies
        super.onViewCreated(view, savedInstanceState)
        val activity = requireActivity()
        wishListModel = ViewModelProvider(activity)[WishListModel::class.java]
        binding.submitButton.setOnClickListener {
            saveAction()
        }
    }

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View?
    {
        // bidning to the View, as the Fragmentbottom got inflated
        binding = FragmentNewWishListBinding.inflate(inflater, container, false)
        return binding.root
    }

    private fun saveAction()
    {
        // Save the data to the ViewHolder layout
        val name = binding.bitFitName.text.toString()
        val caloriesAmount = binding.calories.text.toString()
        val link = binding.time.text.toString()

        val newWish = WishListItem(name, caloriesAmount, link)

        // This is magic ngl
        wishListModel.addWishListItem(newWish)

        // Same thing, tested, clear output
        binding.bitFitName.text?.clear()
        binding.calories.text?.clear()
        binding.time.text?.clear()

        // reset fragments
        dismiss()

    }


}