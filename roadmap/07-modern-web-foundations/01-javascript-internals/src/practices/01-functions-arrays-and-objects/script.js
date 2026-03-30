function initForm() {
    const form = document.querySelector('.form');
    const result = document.querySelector('.result');
    const people = [];

    // querySelector relativo ao elemento pai, busca apenas dentro do 'form'
    const readFields = () => {
        const firstName = form.querySelector('.name').value;
        const lastName = form.querySelector('.second-name').value;
        const weight = form.querySelector('.weight').value;
        const height = form.querySelector('.height').value;

        console.log(`Name: ${firstName} ${lastName} | Weight: ${weight}kg | Height: ${height}m`);

        const person = {
            firstName,
            lastName,
            weight,
            height,
        };

        people.push(person);
        console.log(people);

        result.innerHTML += `<p>Name: ${firstName} | Second Name: ${lastName} | Weight: ${weight} | Height: ${height}</p>`
    };

    // addEventListener permite múltiplos ouvintes no mesmo evento
    // sem sobrescrever os anteriores
    form.addEventListener('submit', (event) => {
        event.preventDefault();
        readFields();
    });
}

initForm();
