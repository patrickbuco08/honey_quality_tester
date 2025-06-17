#pragma once

const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>Honey Quality Tester</title>
    <style>
      body {
        font-family: Arial, sans-serif;
        background: #fdfdfb;
        padding: 20px;
        color: #333;
      }
      h1 {
        color: #a86e00;
        text-align: center;
        margin-bottom: 20px;
      }
      .section {
        border-radius: 12px;
        padding: 16px;
        margin-bottom: 20px;
        box-shadow: 0 4px 16px 0 rgba(0,0,0,0.08), 0 1.5px 5px 0 rgba(0,0,0,0.06);
        background: #fff;
      }
      .section h2 {
        font-size: 1.1em;
        margin-bottom: 10px;
        color: #555;
      }
      .field-group {
        display: flex;
        flex-wrap: wrap;
        gap: 10px;
      }
      .field {
        flex: 1 1 160px;
      }
      label {
        display: block;
        margin-bottom: 4px;
        font-size: 0.9em;
      }
      input[type="text"] {
        padding: 6px 8px;
        font-size: 1em;
        border: 1px solid #ccc;
        border-radius: 4px;
      }
      .buttons {
        display: flex;
        flex-wrap: wrap;
        gap: 10px;
        margin-top: 10px;
      }
      button {
        padding: 10px 16px;
        font-size: 0.9em;
        border: none;
        border-radius: 4px;
        cursor: pointer;
      }
      .btn-analyze {
        background-color: #ffcc00;
        color: #000;
      }
      .btn-calibrate {
        background-color: #0099cc;
        color: white;
      }
      .result {
        padding: 10px;
        background-color: #ffe5b4;
        border-radius: 6px;
        font-weight: bold;
      }
      .note {
        color: red;
        margin-top: 10px;
        font-size: 0.9em;
      }
    .note {
      color: #b71c1c;
      margin-top: 10px;
      font-size: 0.98em;
    }
    .pns-table {
      width: 100%;
      border-collapse: collapse;
      margin-top: 8px;
      background: #222;
      color: #fff;
      font-size: 1em;
      border-radius: 8px;
      overflow: hidden;
      box-shadow: 0 2px 8px rgba(0,0,0,0.06);
    }
    .pns-table th, .pns-table td {
      border-bottom: 1px solid #444;
      padding: 10px 14px;
      text-align: left;
    }
    .pns-table th {
      background: #333;
      font-weight: bold;
      font-size: 1.05em;
      color: #fff;
    }
    .pns-table tr:last-child td {
      border-bottom: none;
    }
    .pns-table em {
      color: #ffccbc;
      font-style: italic;
    }
    .note strong {
      color: #ff5252;
      display: block;
      margin-bottom: 6px;
    }
    </style>
  </head>
  <body>
    <h1>Honey Quality Tester</h1>

    <div class="section">
      <h2>Sensor Readings</h2>
      <div class="field-group">
        <div class="field">
          <label for="phValue">pH Value:</label
          ><input type="text" id="phValue" readonly />
        </div>
        <div class="field">
          <label for="ECValue">EC Value (us/cm):</label
          ><input type="text" id="ECValue" readonly />
        </div>
        <div class="field">
          <label for="moistureValue">Moisture (%):</label
          ><input type="text" id="moistureValue" readonly />
        </div>
        <div class="field">
          <label for="spectroscopyMoisture">Spectroscopy Moisture (%):</label
          ><input type="text" id="spectroscopyMoisture" readonly />
        </div>
      </div>
    </div>

    <div class="section">
      <div class="note">
        <strong>According to the Philippine National Standard (PNS/BAFS __:2022), honey should have:</strong>
        <table class="pns-table">
          <thead>
            <tr>
              <th>Moisture Content</th>
              <th>Electrical Conductivity (EC)</th>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td>&le; 20% <em>(Apis mellifera, cerana)</em></td>
              <td>&le; 0.8 mS/cm</td>
            </tr>
            <tr>
              <td>&le; 23% <em>(wild honey)</em></td>
              <td>&ge; 0.8 mS/cm <span style="font-size:0.95em;">(honeydew/chestnut)</span></td>
            </tr>
            <tr>
              <td>&le; 24% <em>(stingless bee honey)</em></td>
              <td></td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>

    <div class="section">
      <h2>Ambient Reading</h2>
      <div class="field-group">
        <div class="field">
          <label for="tempValue">Temperature (°C):</label
          ><input type="text" id="tempValue" readonly />
        </div>
        <div class="field">
          <label for="humidityValue">Relative Humidity (%):</label
          ><input type="text" id="humidityValue" readonly />
        </div>
      </div>
    </div>

    <div class="section">
      <h2>Absorbance Readings</h2>
      <div class="field-group">
        <div class="field">
          <label for="violetCh1Value">Violet Ch1:</label
          ><input type="text" id="violetCh1Value" readonly />
        </div>
        <div class="field">
          <label for="violetCh2Value">Violet Ch2:</label
          ><input type="text" id="violetCh2Value" readonly />
        </div>
        <div class="field">
          <label for="blueValue">Blue:</label
          ><input type="text" id="blueValue" readonly />
        </div>
        <div class="field">
          <label for="greenCh4Value">Green Ch4:</label
          ><input type="text" id="greenCh4Value" readonly />
        </div>
        <div class="field">
          <label for="greenCh5Value">Green Ch5:</label
          ><input type="text" id="greenCh5Value" readonly />
        </div>
        <div class="field">
          <label for="orangeValue">Orange:</label
          ><input type="text" id="orangeValue" readonly />
        </div>
        <div class="field">
          <label for="redCh7Value">Red Ch7:</label
          ><input type="text" id="redCh7Value" readonly />
        </div>
        <div class="field">
          <label for="redCh8Value">Red Ch8:</label
          ><input type="text" id="redCh8Value" readonly />
        </div>
        <div class="field">
          <label for="clearValue">Clear:</label
          ><input type="text" id="clearValue" readonly />
        </div>
        <div class="field">
          <label for="nirValue">Near-IR:</label
          ><input type="text" id="nirValue" readonly />
        </div>
      </div>
    </div>

    <div class="section">
      <h2>Calibration Buttons</h2>
      <div class="buttons">
        <button id="calibratePH4" class="btn-calibrate">
          Calibrate pH Sensor (4.01)
        </button>
        <button id="calibratePH9" class="btn-calibrate">
          Calibrate pH Sensor (9.18)
        </button>
        <button id="calibrateEC1" class="btn-calibrate">
          Calibrate EC Sensor (1413)
        </button>
        <button id="calibrateEC2" class="btn-calibrate">
          Calibrate EC Sensor (1288)
        </button>
        <button id="calibrateAS7341" class="btn-calibrate">
          Calibrate AS7341
        </button>
      </div>
    </div>

    <div class="section">
      <h2>Analyze Honey Sample</h2>
      <button id="startAnalysis" class="btn-analyze">Start Analysis</button>
      <div id="note" class="note"></div>
    </div>

    <script>
      // --- Helper functions ---
      function disableButtons() {
        document
          .querySelectorAll(".btn-calibrate, .btn-analyze")
          .forEach((btn) => (btn.disabled = true));
      }
      function enableButtons() {
        document
          .querySelectorAll(".btn-calibrate, .btn-analyze")
          .forEach((btn) => (btn.disabled = false));
      }

      // --- Fetch and populate fields ---
      function fetchLatestLog() {
        fetch("/latestLog")
          .then((response) => response.json())
          .then((data) => {
            document.getElementById("phValue").value = data.pH;
            document.getElementById("ECValue").value = data.ec;
            document.getElementById("moistureValue").value = data.moisture;
            document.getElementById("spectroscopyMoisture").value = data.spectroscopyMoisture; // Now using the dedicated spectroscopyMoisture value
            document.getElementById("tempValue").value = data.temperature;
            document.getElementById("humidityValue").value = data.humidity;
            document.getElementById("violetCh1Value").value =
              data.Spectrum[0].violetCh1;
            document.getElementById("violetCh2Value").value =
              data.Spectrum[0].violetCh2;
            document.getElementById("blueValue").value = data.Spectrum[0].blue;
            document.getElementById("greenCh4Value").value =
              data.Spectrum[0].greenCh4;
            document.getElementById("greenCh5Value").value =
              data.Spectrum[0].greenCh5;
            document.getElementById("orangeValue").value =
              data.Spectrum[0].orange;
            document.getElementById("redCh7Value").value =
              data.Spectrum[0].redCh7;
            document.getElementById("redCh8Value").value =
              data.Spectrum[0].redCh8;
            document.getElementById("clearValue").value =
              data.Spectrum[0].clear;
            document.getElementById("nirValue").value = data.Spectrum[0].nir;
            document.getElementById("assessment").value = data.assessment;
          })
          .catch((error) => {
            console.error("Error fetching latest log:", error);
            document.getElementById("note").innerText =
              "Note: Unable to fetch log data.";
          });
      }

      // --- Calibration and Analysis ---
      function getCalibrationUrl(type) {
        switch (type) {
          case "pH4":
            return "/calibratePH4";
          case "pH9":
            return "/calibratePH9";
          case "EC1":
            return "/calibrateEC1";
          case "EC2":
            return "/calibrateEC2";
          case "AS7341":
            return "/calibrateAS7341";
          default:
            return "";
        }
      }

      function calibrate(type) {
        disableButtons();
        const btnMap = {
          pH4: "calibratePH4",
          pH9: "calibratePH9",
          EC1: "calibrateEC1",
          EC2: "calibrateEC2",
          AS7341: "calibrateAS7341"
        };
        const btnId = btnMap[type];
        const btn = document.getElementById(btnId);
        const defaultText = btn ? btn.textContent : "";
        if (btn) btn.textContent = "Calibrating... please wait.";
        document.getElementById("note").innerText = `Calibrating ${type}... please wait.`;
        const url = getCalibrationUrl(type);
        if (!url) {
          document.getElementById("note").innerText = `Unknown calibration type: ${type}`;
          if (btn) btn.textContent = defaultText;
          enableButtons();
          return;
        }
        fetch(url)
          .then((response) => response.json())
          .then((data) => {
            document.getElementById("note").innerText = data.message;
          })
          .catch((error) => {
            document.getElementById("note").innerText = `Error calibrating ${type}: ${error.message}`;
            console.error("Calibration error:", error);
          })
          .finally(() => {
            enableButtons();
            if (btn) btn.textContent = defaultText;
          });
      }

      function startAnalysis() {
        disableButtons();
        const analyzeBtn = document.getElementById("startAnalysis");
        const noteEl = document.getElementById("note");
        const defaultText = "Start Analysis";
        analyzeBtn.textContent = "Analyzing...";
        noteEl.innerText = "";
        fetch("/startAnalysis")
          .then((response) => response.json())
          .then((data) => {
            noteEl.innerText = data.message;
            fetchLatestLog();
          })
          .catch((error) => {
            noteEl.innerText = "Note: Analysis could not be started.";
          })
          .finally(() => {
            enableButtons();
            analyzeBtn.textContent = defaultText;
          });
      }

      // --- Event listeners ---
      window.addEventListener("DOMContentLoaded", () => {
        fetchLatestLog();
        // Attach calibration listeners
        document
          .getElementById("calibratePH4")
          .addEventListener("click", () => calibrate("pH4"));
        document
          .getElementById("calibratePH9")
          .addEventListener("click", () => calibrate("pH9"));
        document
          .getElementById("calibrateEC1")
          .addEventListener("click", () => calibrate("EC1"));
        document
          .getElementById("calibrateEC2")
          .addEventListener("click", () => calibrate("EC2"));
        document
          .getElementById("calibrateAS7341")
          .addEventListener("click", () => calibrate("AS7341"));
        // Attach analysis listener
        document
          .getElementById("startAnalysis")
          .addEventListener("click", startAnalysis);
      });
    </script>
  </body>
</html>
)rawliteral";
