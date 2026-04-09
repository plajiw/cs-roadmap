// Function declaration sofre hoisting — o motor JS eleva a declaração inteira
// para o topo do escopo, então pode ser chamada antes de aparecer no código.

function somar(a, b) {
    return a + b;
}

console.log(somar(2, 3)); // 5


// Function expression NÃO sofre hoisting do valor. A variável é elevada,
// mas fica undefined até essa linha ser executada.

const subtrair = function(a, b) {
    return a - b;
};

console.log(subtrair(5, 2)); // 3


// Arrow function — sintaxe reduzida do ES6. Quando o corpo tem só uma expressão,
// o return é implícito. Não tem seu próprio 'this', 'arguments' nem 'prototype'.

const multiplicar = (a, b) => a * b;

console.log(multiplicar(3, 4)); // 12

// Com lógica interna o bloco {} é necessário e o return passa a ser obrigatório
const dividir = (a, b) => {
    if (b === 0) return null;
    return a / b;
};


// Parâmetro padrão (default parameter) — ES6+
// Se o argumento não for passado ou for undefined, usa o valor padrão.

function saudar(nome = 'visitante') {
    console.log(`Olá, ${nome}!`);
}

saudar();       // "Olá, visitante!"
saudar('Ana');  // "Olá, Ana!"


// Rest parameter (...) agrupa todos os argumentos extras em um array.
// Deve ser sempre o último parâmetro.

function somarTodos(...numeros) {
    return numeros.reduce((acc, n) => acc + n, 0);
}

console.log(somarTodos(1, 2, 3, 4)); // 10


// Closure — uma função "fecha" sobre as variáveis do escopo onde foi criada.
// Mesmo depois que o escopo externo encerrou, a função interna ainda acessa
// aquelas variáveis. Muito usado para criar estado privado.

function criarContador() {
    let count = 0; // inacessível de fora, mas a função interna enxerga

    return function() {
        count++;
        return count;
    };
}

const contador = criarContador();
console.log(contador()); // 1
console.log(contador()); // 2
console.log(contador()); // 3


// IIFE (Immediately Invoked Function Expression) — executada imediatamente
// após ser definida. Cria um escopo isolado sem poluir o escopo global.

(function() {
    const mensagem = 'Executado imediatamente';
    console.log(mensagem);
})();

// Versão com arrow function
(() => {
    console.log('IIFE com arrow function');
})();


// Higher-order function — qualquer função que recebe outra função como
// argumento ou retorna uma função. É o que torna map, filter e reduce possíveis.

function executar(fn, valor) {
    return fn(valor);
}

console.log(executar(n => n * 2, 5)); // 10


// Function factory — retorna uma função configurada com um valor fixado.
// Cada chamada cria uma nova função independente via closure.

function multiplicadorDe(fator) {
    return (numero) => numero * fator;
}

const dobrar    = multiplicadorDe(2);
const triplicar = multiplicadorDe(3);

console.log(dobrar(5));    // 10
console.log(triplicar(5)); // 15


// map, filter e reduce são higher-order functions nativas de array.
// Recebem um callback e iteram sobre os elementos.

const numeros = [1, 2, 3, 4, 5];

const dobrados = numeros.map(n => n * 2);        // [2, 4, 6, 8, 10]
const pares    = numeros.filter(n => n % 2 === 0); // [2, 4]
const soma     = numeros.reduce((acc, n) => acc + n, 0); // 15


// Recursão — função que chama a si mesma. Precisa de um caso base
// para parar, senão estoura a pilha de chamadas (stack overflow).

function fatorial(n) {
    if (n <= 1) return 1;       // caso base
    return n * fatorial(n - 1); // chamada recursiva
}

console.log(fatorial(5)); // 120


// async/await — açúcar sintático sobre Promises. Permite escrever
// código assíncrono com aparência síncrona e tratar erros com try/catch.
// Uma função async sempre retorna uma Promise.

async function buscarDados(url) {
    try {
        const response = await fetch(url);
        const data = await response.json();
        return data;
    } catch (error) {
        console.error('Erro ao buscar:', error);
    }
}


// Currying — transformar uma função de múltiplos argumentos em uma cadeia
// de funções de um argumento cada. Útil para criar funções parcialmente aplicadas.

const add = a => b => a + b;

const add10 = add(10);
console.log(add10(5));  // 15
console.log(add(3)(4)); // 7


// Composição de funções — combinar funções pequenas para formar uma
// transformação maior. O resultado de uma é a entrada da próxima.

const trim      = str => str.trim();
const lowercase = str => str.toLowerCase();
const replace   = str => str.replace(/\s+/g, '-');

const slugify = str => replace(lowercase(trim(str)));

console.log(slugify('  Olá Mundo  ')); // "olá-mundo"

// Utilitário genérico de composição — aplica as funções da direita para a esquerda
const compose = (...fns) => x => fns.reduceRight((v, f) => f(v), x);

const slugifyCompose = compose(replace, lowercase, trim);
console.log(slugifyCompose('  Olá Mundo  ')); // "olá-mundo"
