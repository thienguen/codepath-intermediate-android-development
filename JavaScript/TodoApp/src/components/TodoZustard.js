import create from "zustand";
import { v4 as uuidv4 } from "uuid";

const setDeleteTodo = (set) => (todoId) => {
  set((state) => {
    return {
      todos: state.todos.filter((todo) => todo.id !== todoId),
    };
  });
};

const getLocalTodos = (key) => {
  if (localStorage.getItem(key) === null) {
    localStorage.setItem(key, JSON.stringify([]));
  } else {
    try {
      // @ts-ignore
      let todoLocal = JSON.parse(localStorage.getItem(key) || "");
      return todoLocal;
    } catch (e) {}
  }
};

export const useTodoStore = create((set) => ({
  todos: getLocalTodos("todos") ?? [],
  createNewTodo: (text) =>
    set((state) => ({
      todos: [...state.todos, { id: uuidv4(), text: text, completed: false }],
    })),
  deleteTodo: setDeleteTodo(set),
}));
