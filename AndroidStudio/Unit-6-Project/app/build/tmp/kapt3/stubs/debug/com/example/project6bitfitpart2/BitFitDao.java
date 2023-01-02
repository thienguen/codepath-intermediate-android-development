package com.example.project6bitfitpart2;

import java.lang.System;

@androidx.room.Dao()
@kotlin.Metadata(mv = {1, 7, 1}, k = 1, d1 = {"\u0000 \n\u0002\u0018\u0002\n\u0002\u0010\u0000\n\u0000\n\u0002\u0010\u0002\n\u0000\n\u0002\u0018\u0002\n\u0002\u0010 \n\u0002\u0018\u0002\n\u0002\b\u0005\bg\u0018\u00002\u00020\u0001J\b\u0010\u0002\u001a\u00020\u0003H\'J\u0014\u0010\u0004\u001a\u000e\u0012\n\u0012\b\u0012\u0004\u0012\u00020\u00070\u00060\u0005H\'J\u0010\u0010\b\u001a\u00020\u00032\u0006\u0010\t\u001a\u00020\u0007H\'J\u0016\u0010\n\u001a\u00020\u00032\f\u0010\u000b\u001a\b\u0012\u0004\u0012\u00020\u00070\u0006H\'\u00a8\u0006\f"}, d2 = {"Lcom/example/project6bitfitpart2/BitFitDao;", "", "deleteAll", "", "getAll", "Lkotlinx/coroutines/flow/Flow;", "", "Lcom/example/project6bitfitpart2/BitFitEntity;", "insert", "bitfitItem", "insertAll", "bitfitItems", "app_debug"})
public abstract interface BitFitDao {
    
    @org.jetbrains.annotations.NotNull()
    @androidx.room.Query(value = "SELECT * FROM bitfit_table")
    public abstract kotlinx.coroutines.flow.Flow<java.util.List<com.example.project6bitfitpart2.BitFitEntity>> getAll();
    
    @androidx.room.Insert()
    public abstract void insertAll(@org.jetbrains.annotations.NotNull()
    java.util.List<com.example.project6bitfitpart2.BitFitEntity> bitfitItems);
    
    @androidx.room.Insert()
    public abstract void insert(@org.jetbrains.annotations.NotNull()
    com.example.project6bitfitpart2.BitFitEntity bitfitItem);
    
    @androidx.room.Query(value = "DELETE FROM bitfit_table")
    public abstract void deleteAll();
}