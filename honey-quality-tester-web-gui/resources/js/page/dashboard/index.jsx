import React from "react";
import ReactDOM from "react-dom/client";
import RenameSample from "@components/RenameSample";

document.addEventListener("DOMContentLoaded", () => {
    try {
        const el = document.getElementById("rename-sample");

        if (el) {
            const sampleId = el.dataset.sampleId;
            const sampleName = el.dataset.sampleName;
            ReactDOM.createRoot(el).render(<RenameSample sampleId={sampleId} sampleName={sampleName} />);
        }
    } catch (error) {
        console.error("React render error:", error);
    }
});
