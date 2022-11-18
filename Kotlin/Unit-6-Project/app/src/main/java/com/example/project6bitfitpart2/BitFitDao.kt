package com.example.project6bitfitpart2

import androidx.room.Dao
import androidx.room.Delete
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface BitFitDao {
    @Query("SELECT * FROM bitfit_table")
    fun getAll(): Flow<List<BitFitEntity>>

    @Insert
    fun insertAll(bitfitItems: List<BitFitEntity>)

    @Insert
    fun insert(bitfitItem: BitFitEntity)

    @Query("DELETE FROM bitfit_table")
    fun deleteAll()
}