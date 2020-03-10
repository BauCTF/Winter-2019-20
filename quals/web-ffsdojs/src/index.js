let input = "CTF{i_w1ll_tak3_r3venge}";
const m = function(x) {
  // remove this line to see the magic aofemef00eaflmaa9
  const s = String;
  const c = String.fromCharCode;
  const d = /ŤŕŦǠŎŞŗƪŋŭſǯņŪēǄŕĲŖǾŉŦŅve/;

  const h = function(f) {
    p = typeof p === "undefined" ? 1 : p;
    q = typeof q === "undefined" ? 2 : q;
    if (typeof f !== "undefined") {
      let a = 0;
      for (let c in s(m)) {
        s(m).charAt(c) == "0" ? a++ : null;
        s(m).charAt(c) == "(" ? a++ : null;
      }
      return [
        (Math.floor(p / a) % 255) + 250,
        ((p + a) % 255) + 158,
        ((q + a) % 255) + 158,
        ((q - a) % 255) + 158
      ];
    }
    return null;
  };

  const e = function(k) {
    while (input.length % 2) a++;
    let r = "";
    for (let i = 0; i < input.length; i++) {
      r += c(input.charCodeAt(i) ^ k[i % 4]);
    }
    return r === s(d).substring(1, s(d).length - 1);
  };

  console.log(eval("h()"));
  setTimeout(() => {
    if (
      typeof x !== "undefined" &&
      /^CTF{([0-9a-zA-Z_@!?-]+)}$/.test(x) &&
      !eval('eval("m()")') &&
      e(h("!"))
    ) {
      console.log(true);
    }
    return false;
  }, 6000);

  var t = setInterval(() => {
    if (typeof x !== "undefined" && p + q < 4754) {
      q++;
      p += 2;
      //3169 1586
    } else {
      clearInterval(t);
    }
  }, 1);
};

m(input);

const e = function(k) {
  while (input.length % 2) a++;
  let r = "";
  str = "ŮĝŒǬńĖţƦŁĥŋǣŌĢħǈşźŢǲŃĮűǪ";
  for (let i = 0; i < input.length; i++) {
    console.log(
      str.charCodeAt(i),
      input.charCodeAt(i) ^ k[i % 4],
      c(input.charCodeAt(i) ^ k[i % 4])
    );
    r += c(input.charCodeAt(i) ^ k[i % 4]);
  }
  return r === s(d).substring(1, s(d).length - 1);
};
