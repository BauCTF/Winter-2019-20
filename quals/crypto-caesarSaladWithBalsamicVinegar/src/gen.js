code = "KXMAXBIKLDFQMKMZBVQHMAXVIA";

letters = [];
a1 = [];
a2 = [];
a3 = [];

length = code.length;

for (let i = 0; i < length; i++) {
  letters.push(code.charCodeAt(i));
}

for (let i = 0; i < length; i++) {
  a1.push(Math.floor(Math.random() * 30) + 1);
  a2.push(Math.floor(Math.random() * 30) + 1);
  a3.push(letters[i] - a1[i] - a2[i]);
}

for (let i = 0; i < length; i++) {
  a1[i] = a1[i].toString(16);
  a2[i] = a2[i].toString(16);
  a3[i] = a3[i].toString(16);
}

console.log(a1);
console.log(a2);
console.log(a3);
