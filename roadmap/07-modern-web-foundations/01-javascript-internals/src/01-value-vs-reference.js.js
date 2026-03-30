// Valores primitivos (string, number, boolean, null, undefined) são copiados por valor
let x = 10;
let y = x; // y recebe uma cópia do valor de x
y = 20; // Modificar y não afeta x

console.log("x:", x);
console.log("y:", y);

// Valores referenciados (arrays, objetos e funções) são copiados por referência de memória
let a = [1, 2, 3];
let b = a;
let c = [...a]; // Operador de espalhamento (spread) para criar uma cópia de referência

a.push(4);
a.push(5);
a.pop();

console.log("a:", a);
console.log("b:", b);
console.log("c:", c, "(c é uma cópia de a, não é afetada pelas mudanças em a)");

const obj1 = {
    name: "Alice",
    age: 30
};

const obj2 = obj1; // obj2 é uma referência ao mesmo objeto
const obj3 = { ...obj1 }; // obj3 é uma cópia do objeto obj1

obj1.age = 31; // Modificar obj1 afeta obj2, mas não obj3

console.log("obj1:", obj1);
console.log("obj2:", obj2);
console.log("obj3:", obj3, "(obj3 é uma cópia de obj1, não é afetada pelas mudanças em obj1)");