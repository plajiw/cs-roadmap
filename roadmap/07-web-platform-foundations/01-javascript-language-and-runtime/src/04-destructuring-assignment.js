let a = 'A';
let b = 'B';
let c = 'C';

const numeros = [3, 2, 1];
const letras = [b, c, a];

// Estrutura de desestruturação, onde as variáveis a, b e c recebem os valores correspondentes do array à direita
[a, b, c] = [1, 2, 3];

// Atribuição via desestruturação de array
[a, b, c] = numeros;
[a, b, c] = letras;

const nums = [1, 2, 3, 4, 5];

console.log("Atribuição tradicional por indexação:");
const primeiroNumero = nums[0];
console.log(primeiroNumero);

console.log("\nAtribuição via desestruturação de array:");
const [primeiro, segundo, ...resto] = nums;
console.log(primeiro);
console.log(segundo);
console.log(resto); // O operador rest (...) é usado para coletar o restante dos elementos do array em uma nova variável chamada "resto"


console.log("\nAtribuição via desestruturação de objeto:");
const usuario = {
    nome: "Pablo",
    idade: 22,
    cargo: "Desenvolvedor",
    enderesso: {
        rua: "Rua A",
        numero: 123,
        cidade: "São Paulo"
    }
}

const { nome, idade, cargo } = usuario;
const { enderesso: { rua, numero } } = usuario;

console.log(nome);
console.log(idade);
console.log(cargo);
console.log(rua);
console.log(numero);

console.log("\nAtribuição via desestruturação de matriz:");

//                   0          1          2
//                0  1  2    0  1  2    0  1  2
const matriz = [ [1, 2, 3], [4, 5, 6], [7, 8, 9] ];
// console.log(matriz[0][1]); // Acessando o elemento 2 da primeira submatriz

const [, [,,seis]] = matriz; // Ignorando a primeira submatriz e os dois primeiros elementos da segunda submatriz
console.log(seis); // Imprime o número 6, que é o terceiro elemento da segunda submatriz. Maneira complexa e não recomendada

const [lista1, lista2, lista3] = matriz; // Atribuindo cada submatriz a uma variável separada
console.log(lista1);
console.log(lista1[1]);