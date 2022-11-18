package com.happytimes.alisha.flixtr.helper;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;

/**
 * Created by alishaalam on 7/19/16.
 */
public final class Mapper {
    private static ObjectMapper MAPPER;

    public static ObjectMapper get()
    {
        if (MAPPER == null)
        {
            MAPPER = new ObjectMapper();

            // This is useful for me in case I add new object properties on the server side which are not yet available on the client.
            MAPPER.configure(DeserializationFeature.FAIL_ON_IGNORED_PROPERTIES, false);
        }

        return MAPPER;
    }

    public static String string(Object data)
    {
        try
        {
            return get().writeValueAsString(data);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }

    public static <T> T objectOrThrow(String data, Class<T> type) throws JsonParseException, JsonMappingException, IOException
    {
        return get().readValue(data, type);
    }

    public static <T> T object(String data, Class<T> type)
    {
        try
        {
            return objectOrThrow(data, type);
        }
        catch (Exception e)
        {
            e.printStackTrace();
            return null;
        }
    }
}

