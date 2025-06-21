import { defineConfig } from "vite";
import laravel from "laravel-vite-plugin";

export default defineConfig({
    server: {
        host: "localhost",
        port: 5173,
        strictPort: true,
        origin: "http://localhost:5173",
        cors: true,
        hmr: {
            host: "localhost",
        },
    },
    plugins: [
        laravel({
            input: [
                "resources/css/app.css",
                "resources/js/app.js",
                "resources/js/dashboard.js",
            ],
            refresh: true,
        }),
    ],
});
