import React from "react";

// import components
import Todo from "./Todo";

/* 
  Each todo in todo list has a unique key, use Map to list out the todo list
*/
const TodoList = ({ setTodos, todos, filteredTodos }) => {
  return (
    <div className="todo-container">
      <ul className="todo-list">
        {filteredTodos.map((todo) => (
          <Todo
            setTodos={setTodos}
            todos={todos}
            key={todo.id}
            todo={todo}
            text={todo.text}
          />
        ))}
      </ul>
    </div>
  );
};
export default TodoList;
