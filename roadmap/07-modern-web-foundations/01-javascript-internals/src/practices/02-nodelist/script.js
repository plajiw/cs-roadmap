const paragrafos = document.querySelector('.paragrafos');
const ps = paragrafos.querySelectorAll('p'); // Retorna uma NodeList, não um Array

console.log(ps); // NodeList(3) [p, p, p]
console.log(ps[0]);
console.log(ps.length);

// NodeList é uma coleção de nós, mas não é um Array. Ele tem algumas semelhanças, mas não possui todos os métodos de um Array
console.log(ps.forEach);
console.log(ps.map); // undefined

for (let p in ps) {
    console.log(p);
}

for (let p of ps) {
    console.log(p);
}

const psArray = Array.from(ps); // Converter NodeList para Array
console.log(psArray);
console.log(psArray.map(p => p.textContent)); // Agora podemos usar métodos de Array, como map

const estilosBody = getComputedStyle(document.body);
const backgroundColorBody = estilosBody.backgroundColor;
console.log(backgroundColorBody);

for (let p of ps) {
    p.style.backgroundColor = backgroundColorBody;
    p.style.color = 'red';
}
