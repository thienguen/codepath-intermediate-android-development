import { addTodo } from "./helper";

describe("addTodo", () => {
  it("should return an array", () => {
    const result = addTodo();
    expect(Array.isArray(result)).toBe(true);
  });

  it("should return an array with one object", () => {
    const result = addTodo();
    expect(result.length).toBe(1);
  }, 10000);

  it("should return an array with an object that has a type property", () => {
    const result = addTodo();
    expect(result[0]).toHaveProperty("type");
  });

  it("should return an array with an object that has a payload property", () => {
    const result = addTodo();
    expect(result[0]).toHaveProperty("payload");
  });
});
