#pragma once

const char HTML_PAGE[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Honey Quality Tester</title>
    <style>
      /* CSS Reset by Eric Meyer */
      * {
        margin: 0;
        padding: 0;
        box-sizing: border-box;
      }

      body {
        font-family: Arial, sans-serif;
        background: #fdfdfb;
        color: #333;
        margin: 0;
      }
      h1 {
        color: #daa520;
        text-align: center;
        margin-bottom: 20px;
      }
      .section {
        border-radius: 12px;
        padding: 16px;
        margin-bottom: 20px;
        box-shadow: 0 4px 16px 0 rgba(0, 0, 0, 0.08),
          0 1.5px 5px 0 rgba(0, 0, 0, 0.06);
        background: #fff;
      }
      .navbar {
        width: 100%;
        background: #fff;
        box-shadow: 0 2px 10px 0 rgba(0, 0, 0, 0.1);
        padding: 1rem 0 1rem 0;
        position: sticky;
        top: 0;
        z-index: 10;
        margin-bottom: 18px;
      }
      .navbar-logo {
        font-size: 1.25rem;
        color: #daa520;
        font-weight: bold;
        margin-left: 2.2rem;
        letter-spacing: 1px;
        font-family: inherit;
      }
      .container {
        max-width: 900px;
        margin: 0 auto;
        padding: 0 18px;
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
      .calibration-grid {
        display: grid;
        grid-template-columns: repeat(5, 1fr);
        gap: 12px;
      }
      @media (max-width: 700px) {
        .calibration-grid {
          grid-template-columns: 1fr;
        }
      }
      button {
        padding: 10px 16px;
        font-size: 0.9em;
        border: none;
        border-radius: 0.5rem;
        cursor: pointer;
      }
      .btn-analyze {
        background-color: #daa520;
        color: white;
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
        background: #fff;
        color: #222;
        font-size: 1em;
        border-radius: 8px;
        overflow: hidden;
        box-shadow: 0 2px 8px rgba(0, 0, 0, 0.06);
      }
      .pns-table th,
      .pns-table td {
        border-bottom: 1px solid #e0e0e0;
        padding: 10px 14px;
        text-align: left;
      }
      .pns-table th {
        background: #f5f5f5;
        font-weight: bold;
        font-size: 1.05em;
        color: #daa520;
      }
      .pns-table tr:last-child td {
        border-bottom: none;
      }
      .pns-table em {
        color: #daa520;
        font-style: italic;
      }
      .note strong {
        color: #ff5252;
        display: block;
        margin-bottom: 6px;
      }
      /* Modal for Classes of Honey */
      .info-modal-overlay {
        display: none;
        position: fixed;
        z-index: 1000;
        left: 0;
        top: 0;
        width: 100vw;
        height: 100vh;
        background: rgba(0, 0, 0, 0.32);
        justify-content: center;
        align-items: center;
      }
      .info-modal-overlay.active {
        display: flex;
      }
      .info-modal-content {
        background: #fff;
        padding: 28px 18px 18px 18px;
        border-radius: 12px;
        max-width: 600px;
        width: 96vw;
        box-shadow: 0 8px 32px rgba(0, 0, 0, 0.18);
        position: relative;
      }
      @media (max-width: 700px) {
        .info-modal-content {
          border-radius: 0;
          width: 100vw;
          max-width: 100vw;
          height: 100vh;
          min-height: 100vh;
          box-shadow: none;
          padding: 38px 18px 18px 18px;
        }
      }
      .info-modal-content h2 {
        margin-top: 0;
        font-size: 1.15em;
        color: #daa520;
      }
      .info-modal-content .note {
        margin-top: 0;
        font-size: 0.96em;
      }
      .info-modal-content #closeInfoModal {
        position: absolute;
        top: 10px;
        right: 12px;
        background: none;
        border: none;
        padding: 0;
        font-size: 2em;
        color: #daa520;
        cursor: pointer;
      }
    </style>
  </head>
  <body>
    <nav class="navbar">
      <h1 class="navbar-logo">Honey Quality Tester</h1>
    </nav>

    <div class="container">
      <div class="section">
        <h2>Calibration Buttons</h2>
        <div class="buttons calibration-grid">
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
        <span
          style="
            display: inline-flex;
            align-items: center;
            margin-left: 10px;
            gap: 4px;
          "
        >
          <button
            id="infoButton"
            title="Standard Parameters"
            style="
              background: transparent;
              border: none;
              cursor: pointer;
              padding: 0;
              vertical-align: middle;
              outline: none;
            "
          >
            <svg
              height="22"
              width="22"
              viewBox="0 0 22 22"
              style="vertical-align: middle"
            >
              <circle
                cx="11"
                cy="11"
                r="10"
                fill="none"
                stroke="#DAA520"
                stroke-width="2"
              />
              <text
                x="11"
                y="16"
                text-anchor="middle"
                font-size="13"
                fill="#DAA520"
                font-family="Arial"
                font-weight="bold"
              >
                i
              </text>
            </svg>
          </button>
        </span>
        <div id="note" class="note"></div>
      </div>
    </div>
    <!-- end container -->

    <!-- Info Modal for Classes of Honey -->
    <div id="infoModal" class="info-modal-overlay">
      <div class="info-modal-content">
        <button id="closeInfoModal">&times;</button>
        <h2>Classes of Honey for Honey Quality Tester</h2>
        <table class="pns-table" style="margin-bottom: 10px">
          <thead>
            <tr>
              <th>Moisture Content</th>
              <th>Electrical Conductivity</th>
              <th>pH Value</th>
            </tr>
          </thead>
          <tbody>
            <tr>
              <td>
                &le; 20% <em>(Apis mellifera<br />and Apis cerana)</em>
              </td>
              <td>
                &lt; 0.8 mS/cm
                <span style="font-size: 0.95em">(most honey)</span>
              </td>
              <td>&ge; 3.7</td>
            </tr>
            <tr>
              <td>
                &le; 23% <em>(Apis dorsata<br />and Apis breviligula)</em>
              </td>
              <td>
                &gt; 0.8 mS/cm
                <span style="font-size: 0.95em"
                  >(only for chestnut honey, honeydew honey and their
                  blend)</span
                >
              </td>
              <td>&le; 4.5</td>
            </tr>
            <tr>
              <td>&le; 24% <em>(Tetragonula spp.)</em></td>
              <td></td>
              <td></td>
            </tr>
          </tbody>
        </table>
        <div class="note">
          <em
            >The values of parameters are based on the following
            studies/articles: <b>Moisture</b> (Bureau of Agriculture and
            Fisheries Standards [BAFS], 2022),
            <b>Electrical Conductivity</b> (BAFS 2022) and
            <b>pH Values</b> (Codex Standard for Honey [CAC], 1981).</em
          >
        </div>
      </div>
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
            document.getElementById("spectroscopyMoisture").value =
              data.spectroscopyMoisture; // Now using the dedicated spectroscopyMoisture value
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
          AS7341: "calibrateAS7341",
        };
        const btnId = btnMap[type];
        const btn = document.getElementById(btnId);
        const defaultText = btn ? btn.textContent : "";
        if (btn) btn.textContent = "Calibrating... please wait.";
        document.getElementById(
          "note"
        ).innerText = `Calibrating ${type}... please wait.`;
        const url = getCalibrationUrl(type);
        if (!url) {
          document.getElementById(
            "note"
          ).innerText = `Unknown calibration type: ${type}`;
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
            document.getElementById(
              "note"
            ).innerText = `Error calibrating ${type}: ${error.message}`;
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
        // fetchLatestLog();
        // Info Modal functionality
        const infoBtn = document.getElementById("infoButton");
        const infoModal = document.getElementById("infoModal");
        const closeModalBtn = document.getElementById("closeInfoModal");
        if (infoBtn && infoModal && closeModalBtn) {
          infoBtn.addEventListener("click", () => {
            infoModal.classList.add("active");
          });
          closeModalBtn.addEventListener("click", () => {
            infoModal.classList.remove("active");
          });
          infoModal.addEventListener("click", (e) => {
            if (e.target === infoModal) infoModal.classList.remove("active");
          });
        }
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
