//Làm theo Function components
import React from "react";
import logo from "../logo.svg";
import TodoList from "./TodoList";
import TodoForm from "./TodoForm";
import { useState, useEffect } from "react";

/*
  import components as JSX  
  JSX: JavaScript XML, extended syntax of Javascript  which help Devs write HTML in React
  Default root would be src folder, if components are outside 
  of src folder, we need to use relative path or config modules
*/
function Main() {

  /*
    useState hook: Adding state into our functional component
    each having a variable and a function to update the variable
  */
  const [inputText, setInputText] = useState("");
  const [status, setStatus] = useState("all");
  const [todos, setTodos] = useState([]);
  const [filteredTodos, setFilteredTodos] = useState([]);

  /* 
    Everytime dependencies todos, status change => run function filterHandler
    After filterHandler run => run function saveLocalTodos (mean we often have a new todo)
    or user change status of a todo.
  */
  useEffect(() => {
    filterHandler();
    saveLocalTodos();
  }, [todos, status]);

  /* 
    It only run once when the app start, 
    and we get our local todos from local storage (if any)
  */
  useEffect(() => {
    getLocalTodos();
  }, []);

  /* 
    Function filter, filter todos base on status
  */
  const filterHandler = () => {
    switch (status) {
      case "completed":
        // @ts-ignore
        setFilteredTodos(todos.filter((todo) => todo.completed === true));
        break;
      case "uncompleted":
        // @ts-ignore
        setFilteredTodos(todos.filter((todo) => todo.completed === false));
        break;
      default:
        setFilteredTodos(todos);
        break;
    }
  };

  /* 
    Save to local, and parse to JSON as LOCALSTORAGE save JSON
  */
  const saveLocalTodos = () => {
    localStorage.setItem("todos", JSON.stringify(todos));
  };

  /* 
    If page is reload, we get our todos from local storage
    Due to nullable of local storage, I check if we have any todos in there
  */
  const getLocalTodos = () => {
    if (localStorage.getItem("todos") === null) {
      localStorage.setItem("todos", JSON.stringify([]));
    } else {
      try {
        // @ts-ignore
        let todoLocal = JSON.parse(localStorage.getItem("todos") || "");
        setTodos(todoLocal);
      } catch (e) {}
    }
  };

  /*
    Render TodoList and TodoForm components
  */
  return (
    <div className="todo-app">
      {/* The header start here, style it kinda funny */}
      <header>
        <img src={logo} className="Main-logo" alt="logo" />
        <h1>Todo List</h1>
      </header>
      
      {/* Form with 5 props */}
      <TodoForm
        inputText={inputText}
        setInputText={setInputText}
        setTodos={setTodos}
        todos={todos}
        setStatus={setStatus}
      />

      {/* Display todo list */}
      <TodoList
        filteredTodos={filteredTodos}
        setTodos={setTodos}
        todos={todos}
      />
    </div>
  );
}

export default Main;
