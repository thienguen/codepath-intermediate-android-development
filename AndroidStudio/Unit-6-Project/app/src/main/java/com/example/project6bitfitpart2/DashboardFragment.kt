package com.example.project6bitfitpart2

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.launch

class DashboardFragment : Fragment() {

    private lateinit var avgCalTextView: TextView
    private lateinit var maxCalTextView: TextView
    private lateinit var minCalTextView: TextView
    private lateinit var clearDataButton: Button
    private val items = mutableListOf<BitFitItem>()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        var totalCal = 0.0
        var itemNum = 0.0
        var maxCal = 0
        var minCal = 0

        clearDataButton.setOnClickListener {
            avgCalTextView.text = "0.00"
            maxCalTextView.text = "0"
            minCalTextView.text = "0"

            lifecycleScope.launch(IO) {
                (activity?.application as BitFitApplication).db.bitfitDao().deleteAll()
            }
        }

        lifecycleScope.launch {
            (activity?.application as BitFitApplication).db.bitfitDao().getAll().collect { databaseList ->
                databaseList.map { entity ->
                    BitFitItem(
                        entity.itemName,
                        entity.calories
                    ).also {
                        val cal = it.calories?.toInt() ?: 0
                        totalCal += cal
                        itemNum += 1.0
                        maxCal = if (maxCal==0) cal else maxOf(maxCal, cal)
                        minCal = if (minCal==0) cal else minOf(minCal, cal)
                    }
                }.also { mappedList ->
                    items.clear()
                    items.addAll(mappedList)
                    val avgCal = if (itemNum>0) totalCal/itemNum else 0.00
                    avgCalTextView.text = String.format("%.2f", avgCal)
                    maxCalTextView.text = maxCal.toString()
                    minCalTextView.text = minCal.toString()
                }
            }
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_dashboard, container, false)
        avgCalTextView = view.findViewById(R.id.AvgCal)
        minCalTextView = view.findViewById(R.id.MinCal)
        maxCalTextView = view.findViewById(R.id.MaxCal)
        clearDataButton = view.findViewById(R.id.ClearDataButton)

        return view
    }
}