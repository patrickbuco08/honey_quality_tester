import React, { useState } from "react";
import toast, { Toaster } from "react-hot-toast";

export default function RenameSample({ sampleId, sampleName }) {
    const [name, setName] = useState(sampleName || "");
    const [isLoading, setIsLoading] = useState(false);
    const [isEditing, setIsEditing] = useState(!sampleName);

    const handleSubmit = async (e) => {
        e.preventDefault();
        if (isLoading) return;

        setIsLoading(true);

        try {
            const token = document
                .querySelector('meta[name="csrf-token"]')
                .getAttribute("content");

            const response = await fetch(`/honey-samples/${sampleId}/name`, {
                method: "PATCH",
                headers: {
                    "Content-Type": "application/json",
                    Accept: "application/json",
                    "X-CSRF-TOKEN": token,
                    "X-Requested-With": "XMLHttpRequest",
                },
                body: JSON.stringify({ name }),
                credentials: "same-origin",
            });

            const data = await response.json();
            if (!response.ok) {
                throw new Error(data.message || "Failed to update name");
            }

            toast.success(data.message || "Name updated successfully!");
        } catch (error) {
            console.error("Error updating name:", error);
            toast.error(
                error.message || "An error occurred while updating the name"
            );
        } finally {
            setIsLoading(false);
        }
    };

    const handleEditClick = () => {
        setIsEditing(true);
    };

    const handleSave = async (e) => {
        await handleSubmit(e);
        if (name) {
            setIsEditing(false);
        }
    };

    return (
        <div className="flex items-center gap-2">
            <Toaster
                position="top-center"
                toastOptions={{
                    duration: 3000,
                    style: {
                        background: "#DAA520",
                        color: "#fff",
                    },
                    success: {
                        duration: 3000,
                    },
                    error: {
                        duration: 3000,
                    },
                }}
            />

            {!isEditing && name ? (
                <div className="flex items-center gap-2">
                    <span className="font-medium">{name}</span>
                    <button
                        type="button"
                        onClick={handleEditClick}
                        className="text-honey hover:text-honey-dark text-sm"
                    >
                        Edit
                    </button>
                </div>
            ) : (
                <form onSubmit={handleSave} className="flex items-center gap-2">
                    <input
                        type="text"
                        placeholder="Name this sample..."
                        value={name}
                        onChange={(e) => setName(e.target.value)}
                        className="border px-2 py-1 rounded text-sm"
                        autoFocus
                    />
                    <button
                        type="submit"
                        disabled={isLoading}
                        className={`bg-honey text-white px-4 py-1 rounded flex items-center justify-center min-w-[80px] text-sm ${
                            isLoading
                                ? "opacity-70 cursor-not-allowed"
                                : "hover:opacity-90"
                        }`}
                    >
                        {isLoading ? (
                            <>
                                <svg
                                    className="animate-spin -ml-1 mr-2 h-4 w-4 text-white"
                                    xmlns="http://www.w3.org/2000/svg"
                                    fill="none"
                                    viewBox="0 0 24 24"
                                >
                                    <circle
                                        className="opacity-25"
                                        cx="12"
                                        cy="12"
                                        r="10"
                                        stroke="currentColor"
                                        strokeWidth="4"
                                    ></circle>
                                    <path
                                        className="opacity-75"
                                        fill="currentColor"
                                        d="M4 12a8 8 0 018-8V0C5.373 0 0 5.373 0 12h4zm2 5.291A7.962 7.962 0 014 12H0c0 3.042 1.135 5.824 3 7.938l3-2.647z"
                                    ></path>
                                </svg>
                                Saving...
                            </>
                        ) : (
                            "Save"
                        )}
                    </button>
                </form>
            )}
        </div>
    );
}
