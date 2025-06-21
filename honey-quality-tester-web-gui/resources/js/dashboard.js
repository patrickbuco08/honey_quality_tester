import Toastify from "toastify-js";
import "toastify-js/src/toastify.css";

document.addEventListener("DOMContentLoaded", () => {
    const formatDate = (isoString) => {
        const options = {
            year: "numeric",
            month: "long",
            day: "numeric",
            hour: "numeric",
            minute: "2-digit",
            hour12: true,
        };
        return (
            "Date Tested: " +
            new Date(isoString).toLocaleString("en-US", options)
        );
    };

    const fetchLatestSample = async () => {
        try {
            const response = await fetch("/latest-honey-sample");
            const result = await response.json();

            if (result.success && result.sample) {
                const currentSampleId = document
                    .querySelector("[data-sample-id]")
                    ?.getAttribute("data-sample-id");

                console.log(
                    "String(result.sample.id)",
                    String(result.sample.id)
                );
                console.log("currentSampleId", currentSampleId);

                if (String(result.sample.id) !== currentSampleId) {
                    Toastify({
                        text: "🍯 Sweet! A new honey sample just came in!",
                        duration: 5000,
                        gravity: "top", // can also use "bottom"
                        position: "center",
                        style: {
                            background: "#F6BE00",
                            color: "white",
                            boxShadow: "0 10px 15px -3px rgba(0, 0, 0, 0.1)",
                            borderRadius: "0.75rem", // rounded-xl
                            padding: "1rem 1.5rem",
                            fontWeight: "400",
                        },
                    }).showToast();

                    document
                        .querySelector("[data-sample-id]")
                        .setAttribute("data-sample-id", result.sample.id);

                    const {
                        sensor_readings,
                        ambient_reading,
                        absorbance_readings,
                    } = result.sample.data;

                    // Update sensor readings
                    document.getElementById("sensor-ph_value").textContent =
                        sensor_readings.ph_value;
                    document.getElementById("sensor-ec_value").textContent =
                        sensor_readings.ec_value;
                    document.getElementById("sensor-moisture").textContent =
                        sensor_readings.moisture;
                    document.getElementById(
                        "sensor-spectroscopy_moisture"
                    ).textContent = sensor_readings.spectroscopy_moisture;

                    // Update ambient readings
                    document.getElementById("ambient-temperature").textContent =
                        ambient_reading.temperature;
                    document.getElementById("ambient-humidity").textContent =
                        ambient_reading.humidity;

                    // Update absorbance readings
                    document.getElementById(
                        "absorbance-violet_ch1"
                    ).textContent = absorbance_readings.violet_ch1;
                    document.getElementById(
                        "absorbance-violet_ch2"
                    ).textContent = absorbance_readings.violet_ch2;
                    document.getElementById("absorbance-blue").textContent =
                        absorbance_readings.blue;
                    document.getElementById(
                        "absorbance-green_ch4"
                    ).textContent = absorbance_readings.green_ch4;
                    document.getElementById(
                        "absorbance-green_ch5"
                    ).textContent = absorbance_readings.green_ch5;
                    document.getElementById("absorbance-orange").textContent =
                        absorbance_readings.orange;
                    document.getElementById("absorbance-red_ch7").textContent =
                        absorbance_readings.red_ch7;
                    document.getElementById("absorbance-red_ch8").textContent =
                        absorbance_readings.red_ch8;
                    document.getElementById("absorbance-clear").textContent =
                        absorbance_readings.clear;
                    document.getElementById("absorbance-near_ir").textContent =
                        absorbance_readings.near_ir;

                    document.getElementById("date-tested").textContent =
                        formatDate(result.sample.created_at);
                }
            }
        } catch (error) {
            console.error("Error fetching latest sample:", error);
        }
    };

    setInterval(fetchLatestSample, 3000);
});
