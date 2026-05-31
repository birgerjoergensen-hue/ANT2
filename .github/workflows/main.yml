name: Arduino Build und Verpackung

on:
  push:
    branches: [ main, master ]
  pull_request:
    branches: [ main, master ]
  workflow_dispatch:

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
      - name: Code auschecken
        uses: actions/checkout@v4

      - name: Arduino CLI einrichten
        uses: arduino/setup-arduino-cli@v2

      - name: Adafruit Board-Manager hinzufügen
        run: |
          arduino-cli core update-index --additional-urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
          arduino-cli core install adafruit:nrf52 --additional-urls https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

      - name: ANT Bibliothek installieren
        # Wir ziehen die Bibliothek direkt aus dem Repo, damit ANT.h verfügbar ist
        run: |
          arduino-cli lib install --git-url https://github.com/djaustin/nRF52-ANT

      - name: Sketch kompilieren
        run: |
          arduino-cli compile --fqbn adafruit:nrf52:feather52840sense --output-dir ./build .

      - name: Fertige Firmware als ZIP bereitstellen
        uses: actions/upload-artifact@v4
        with:
          name: blipbox-31v29-firmware
          path: ./build/
