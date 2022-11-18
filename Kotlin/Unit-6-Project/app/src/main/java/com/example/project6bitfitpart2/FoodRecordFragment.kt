package com.example.project6bitfitpart2

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.coroutines.launch

class FoodRecordFragment : Fragment() {

    private val items = mutableListOf<BitFitItem>()
    private lateinit var itemAdapter: BitFitAdapter

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        fetchItems()
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_record, container, false)

        val layoutManager = LinearLayoutManager(context)
        val itemRecyclerView = view.findViewById<RecyclerView>(R.id.ItemsListRecyclerView)
        itemRecyclerView.layoutManager = layoutManager
        itemRecyclerView.setHasFixedSize(true)
        itemAdapter = BitFitAdapter(items)
        itemRecyclerView.adapter = itemAdapter

        return view
    }

    companion object {

        fun newInstance() : FoodRecordFragment {
            return FoodRecordFragment()
        }
    }

    private fun fetchItems() {
        lifecycleScope.launch {
            (activity?.application as BitFitApplication).db.bitfitDao().getAll().collect { databaseList ->
                databaseList.map { entity ->
                    BitFitItem(
                        entity.itemName,
                        entity.calories
                    )
                }.also { mappedList ->
                    items.clear()
                    items.addAll(mappedList)
                    itemAdapter.notifyDataSetChanged()
                }
            }
        }
    }

}