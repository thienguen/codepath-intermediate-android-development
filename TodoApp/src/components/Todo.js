import React from "react";
import NotificationProvider, { useNotification } from "use-toast-notification";

const Todo = ({ text, todo, todos, setTodos }) => {
  /*
    Delete Todo: Click the button 
    => get the id of the todo 
    => filter out the todo with the id 
    => set the new todo list
  */
  const deleteHandler = (T) => {
    setTodos(todos.filter((item) => item.id !== todo.id));
  };

  /*
    Completed Todo: Click button complete of 1 todo, 
    => get the id of the todo
    => map through the todo list
    => if the id of the todo is equal to the id of the todo that we click,
    => change the completed status of the todo
    => set the new todo list
  */
  const completeHandler = () => {
    setTodos(
      todos.map((item) => {
        if (item.id === todo.id) {
          return {
            ...item,
            completed: !item.completed,
          };
        }
        return item;
      })
    );
  };

  return (
    <div className="todo">
      <li className={`todo-item ${todo.completed ? "completed" : ""}`}>
        {text}
      </li>
      <button onClick={completeHandler} className="complete-btn">
        <i className="fas fa-check"></i>
      </button>
      <button onClick={deleteHandler} className="trash-btn">
        <i className="fas fa-trash"></i>
      </button>
    </div>
  );
};

export default Todo;
