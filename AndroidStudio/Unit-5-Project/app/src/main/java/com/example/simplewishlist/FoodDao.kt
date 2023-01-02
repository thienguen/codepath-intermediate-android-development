package com.example.simplewishlist

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface FoodDao {
    @Query("SELECT * FROM fitbit_table")
    fun getAll(): Flow<List<FoodEntity>>

    @Insert
    fun insertAll(foods : List<FoodEntity>)

    @Insert
    fun insert(foodEntity: FoodEntity)

    @Query("DELETE FROM fitbit_table")
    fun deleteAll()
}