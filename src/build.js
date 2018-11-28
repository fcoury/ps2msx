const fs = require('fs');

const PS2MAP = `${__dirname}/ps2map.txt`;
const KEYMAP = `${__dirname}/keymap.txt`;
const SOURCE = `${__dirname}/ps2msx.cpp`;

const ps2mapContents = fs.readFileSync(PS2MAP, 'utf8');
const ps2map = ps2mapContents.replace(/\n$/, '').split('\n')
  .map(line => line.split('|'))
  .map(line => line.map(p => p.trim()))
  .reduce((hash, val) => {
    hash[val[0]] = { down: val[1].split(',' ), up: val[2].split(',') };
    return hash;
  }, {});
const keymapContents = fs.readFileSync(KEYMAP, 'utf8');
const keymap = keymapContents.replace(/\n$/, '').split('\n')
  .filter(line => line.indexOf('0x00') == -1)
  .map(line => line.split('|'))
  .map(line => line.map(p => p.trim()))

// keyDown
const keyDownCases = keymap
  .map(km => {
    const usbCode = km[0];
    const usbKey = km[1];
    const ps2Key = km[2];

    const ps2entry = ps2map[ps2Key];
    const kbCommands = ps2entry.down
      .filter(hexCode => hexCode.trim().length > 0)
      .map(hexCode => `    kbSend(${hexCode.trim()});`)
      .join('\n');

    return `  case ${usbCode}: // ${usbKey} -> ${ps2Key} \n${kbCommands}\n    break;\n`;
  }).join('\n');

// keyUp
const keyUpCases = keymap
  .map(km => {
    const usbCode = km[0];
    const usbKey = km[1];
    const ps2Key = km[2];

    const ps2entry = ps2map[ps2Key];
    const kbCommands = ps2entry.up
      .filter(hexCode => hexCode.trim().length > 0)
      .map(hexCode => `    kbSend(${hexCode.trim()});`)
      .join('\n');

    return `  case ${usbCode}: // ${usbKey} -> ${ps2Key}\n${kbCommands}\n    break;\n`;
  }).join('\n');

const codeStr = `// --- (AUTOGEN START) ---
void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  Serial.print("Down ");
  Serial.println(key, HEX);

  Serial.print("DN ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  Serial.print("ASCII: ");
  Serial.println((char)key);

  switch(key) {
${keyDownCases}
  }
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.print("Up ");
  Serial.println(key, HEX);

  Serial.print("UP ");
  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

  Serial.print("ASCII: ");
  Serial.println((char)key);

  switch(key) {
${keyUpCases}
  }
}
// --- (AUTOGEN END) ---`;

const source = fs.readFileSync(SOURCE, 'utf8');
const target = [];

let active = true;
source.split('\n').forEach(line => {
  if (line.indexOf('AUTOGEN START') > -1) {
    active = false;
    target.push(codeStr);
  }
  if (line.indexOf('AUTOGEN END') > -1) {
    active = true;
  } else if (active) {
    target.push(line);
  }
});

const output = target.join('\n');

console.log(` [build] Writing ${SOURCE}...`);
fs.writeFileSync(SOURCE, output, 'utf8');
console.log(` [build] Done.`);
