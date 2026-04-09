// --- ESCOPO DE VARIÁVEIS: let, var e const ---

// let respeita escopo de bloco {}, existe apenas no contexto onde foi declarada
let nome = 'Luiz';
// var é içada (hoisting) para o topo do escopo de função ou global, ignora blocos
var nome2 = 'Luiz';

console.log("Global let:", nome);  // Luiz
console.log("Global var:", nome2); // Luiz

if (true) {
    // SHADOWING: este 'let nome' cria uma variável nova, local ao bloco
    // não altera nem acessa o 'nome' do escopo externo, são variáveis distintas
    let nome = 'Maria';

    // var não cria nova variável aqui, reatribui a mesma 'nome2' do escopo global
    // var tem escopo de função, não de bloco; o bloco if não cria um novo escopo para var
    var nome2 = 'Maria';

    console.log("Local let (Bloco 1): " + nome);      // Maria
    console.log("Var alterada globalmente: " + nome2); // Maria

    if (true) {
        // novo nível de escopo de bloco, este 'nome' só existe aqui dentro
        // ao sair do bloco, essa binding é destruída
        let nome = 'João';
        console.log("Local let (Bloco 2): " + nome); // João
    }
    // aqui 'nome' resolve para o 'Maria' do bloco pai, o 'João' já saiu de escopo
}

console.log("\n--- FORA DOS BLOCOS ---");

// 'nome' global nunca foi alterado, let isola modificações dentro do bloco
console.log("Global let final: " + nome);  // Luiz

// 'nome2' global foi sobrescrito, var dentro do if operou sobre a mesma variável global
console.log("Global var final: " + nome2); // Maria

// --- Hoisting com var ---
// antes da execução, o motor JS varre o código e eleva as declarações var para o topo do escopo
// apenas a declaração sobe, não a atribuição — o valor permanece undefined até a linha ser executada
console.log("Hoisting var antes da declaração:", varHoisting); // undefined
var varHoisting = 'valor definido';
console.log("Após a declaração:", varHoisting); // valor definido

// com let e const o hoisting também ocorre, mas elas ficam na TDZ (Temporal Dead Zone)
// acessar antes da declaração lança ReferenceError, não retorna undefined
// console.log(letHoisting); // ReferenceError: Cannot access 'letHoisting' before initialization
let letHoisting = 'valor';

// --- Var respeitando escopo de função ---
// var vaza de blocos (if, for, while), mas NÃO vaza de funções
// a função cria um novo escopo de execução — var fica presa dentro dele
function exemploVarEmFuncao() {
    var varLocal = 'só existe aqui dentro';
    console.log("Dentro da função:", varLocal); // só existe aqui dentro
}

exemploVarEmFuncao();
// console.log(varLocal); // ReferenceError: varLocal is not defined
// a var declarada dentro da função não é acessível no escopo externo

// --- CONST ---
// const segue as mesmas regras de escopo do let (block-scoped)
// a diferença: o binding não pode ser reatribuído após a inicialização
const pi = 3.14;
// pi = 3.15; // TypeError: Assignment to constant variable