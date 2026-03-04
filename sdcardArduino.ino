#include <SD.h>

#define CS_PIN 10

File root;

void setup() {
  Serial.begin(115200);

  Serial.print("Initializing SD card... ");

  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }

  Serial.println("initialization done.");

  Serial.println("Files in the card:");

  // creamos archivo
  File file = SD.open("datos.txt", FILE_WRITE);
  if (file) {
    file.println("Archivo creado correctamente");
    file.close();
  } else {
    Serial.println("Error creando archivo");
  }
  root = SD.open("/");
  printDirectory(root, 0);
  Serial.println("");


  // leemos
  File textFile = SD.open("datos.txt");
  if (textFile) {
    Serial.print("datos.txt: ");
    while (textFile.available()) {
      Serial.write(textFile.read());
    }
    textFile.close();
  } else {
    Serial.println("error opening datos.txt!");
  }

   // modificamos archivo
  file = SD.open("datos.txt", FILE_WRITE);
  if (file) {
    file.print(" y archivo modificado correctamente");
    file.close();
  } else {
    Serial.println("Error creando archivo");
  }

  // leemos de nuevo
  textFile = SD.open("datos.txt");
  if (textFile) {
    Serial.print("datos.txt: ");
    while (textFile.available()) {
      Serial.write(textFile.read());
    }
    textFile.close();
  } else {
    Serial.println("error opening datos.txt!");
  }
}

void loop() {
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

