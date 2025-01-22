// instalacja typescript (jeśli jeszcze nie jest zainstalowany):
// npm install typescript -g

// 1. funkcja implementująca licznik z wykorzystaniem var i let
function licznikVarLet() {
  var licznikVar = 0;
  let licznikLet = 0;

  licznikVar++;
  licznikLet++;

  console.log(`licznikVar: ${licznikVar}, licznikLet: ${licznikLet}`);
}
licznikVarLet();

// 2. funkcja ze zmienną liczbą atrybutów (operator ...)
function suma(...args: number[]): number {
  return args.reduce((a, b) => a + b, 0);
}
console.log(suma(2)); // 2
console.log(suma(3, 4)); // 7
console.log(suma(1, 2, 3)); // 6

// 3. zdefiniowanie przykładów zmiennych w typescript
const zmiennaString: string = "tekst";
const zmiennaNumber: number = 123;
const zmiennaBoolean: boolean = true;

console.log(zmiennaString, zmiennaNumber, zmiennaBoolean);

// 4. zdefiniowanie interfejsu i funkcji wyświetlającej dane osoby
interface Osoba {
  imie: string;
  nazwisko: string;
  wiek?: number; // opcjonalne
}

function pokazOsobe(osoba: Osoba): void {
  console.log(
    `Imię: ${osoba.imie}, Nazwisko: ${osoba.nazwisko}, Wiek: ${
      osoba.wiek ?? "nie podano"
    }`
  );
}

pokazOsobe({ imie: "Jan", nazwisko: "Kowalski", wiek: 30 });
pokazOsobe({ imie: "Anna", nazwisko: "Nowak" });

// 5. klasa car z trzema obiektami
class Car {
  marka: string;
  model: string;
  rok: number;

  constructor(marka: string, model: string, rok: number) {
    this.marka = marka;
    this.model = model;
    this.rok = rok;
  }

  opis(): string {
    return `${this.marka} ${this.model}, ${this.rok}`;
  }
}

const car1 = new Car("Toyota", "Corolla", 2015);
const car2 = new Car("Honda", "Civic", 2020);
const car3 = new Car("Ford", "Focus", 2018);

console.log(car1.opis());
console.log(car2.opis());
console.log(car3.opis());

// 6. dziedziczenie klasy truck
class Truck extends Car {
  ladownosc: number;

  constructor(marka: string, model: string, rok: number, ladownosc: number) {
    super(marka, model, rok);
    this.ladownosc = ladownosc;
  }

  opis(): string {
    return `${super.opis()} o ładowności ${this.ladownosc} ton`;
  }
}

const truck = new Truck("MAN", "TGX", 2021, 18);
console.log(truck.opis());

// 7. async/await i promise
async function fetchData(): Promise<string> {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve("Dane pobrane pomyślnie!");
    }, 2000);
  });
}

async function pokazDane(): Promise<void> {
  const dane = await fetchData();
  console.log(dane);
}

pokazDane();
