-- -------------------------------------------------------------
-- TablePlus 6.4.8(608)
--
-- https://tableplus.com/
--
-- Database: bocum
-- Generation Time: 2025-06-21 20:22:02.0380
-- -------------------------------------------------------------


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


DROP TABLE IF EXISTS `cache`;
CREATE TABLE `cache` (
  `key` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `value` mediumtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `expiration` int NOT NULL,
  PRIMARY KEY (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `cache_locks`;
CREATE TABLE `cache_locks` (
  `key` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `owner` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `expiration` int NOT NULL,
  PRIMARY KEY (`key`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `failed_jobs`;
CREATE TABLE `failed_jobs` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `uuid` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `connection` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `queue` text COLLATE utf8mb4_unicode_ci NOT NULL,
  `payload` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `exception` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `failed_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `failed_jobs_uuid_unique` (`uuid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `honey_samples`;
CREATE TABLE `honey_samples` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `data` json NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `job_batches`;
CREATE TABLE `job_batches` (
  `id` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `total_jobs` int NOT NULL,
  `pending_jobs` int NOT NULL,
  `failed_jobs` int NOT NULL,
  `failed_job_ids` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `options` mediumtext COLLATE utf8mb4_unicode_ci,
  `cancelled_at` int DEFAULT NULL,
  `created_at` int NOT NULL,
  `finished_at` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `jobs`;
CREATE TABLE `jobs` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `queue` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `payload` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `attempts` tinyint unsigned NOT NULL,
  `reserved_at` int unsigned DEFAULT NULL,
  `available_at` int unsigned NOT NULL,
  `created_at` int unsigned NOT NULL,
  PRIMARY KEY (`id`),
  KEY `jobs_queue_index` (`queue`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `migrations`;
CREATE TABLE `migrations` (
  `id` int unsigned NOT NULL AUTO_INCREMENT,
  `migration` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `batch` int NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `password_reset_tokens`;
CREATE TABLE `password_reset_tokens` (
  `email` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `token` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `personal_access_tokens`;
CREATE TABLE `personal_access_tokens` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `tokenable_type` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `tokenable_id` bigint unsigned NOT NULL,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `token` varchar(64) COLLATE utf8mb4_unicode_ci NOT NULL,
  `abilities` text COLLATE utf8mb4_unicode_ci,
  `last_used_at` timestamp NULL DEFAULT NULL,
  `expires_at` timestamp NULL DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `personal_access_tokens_token_unique` (`token`),
  KEY `personal_access_tokens_tokenable_type_tokenable_id_index` (`tokenable_type`,`tokenable_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `sessions`;
CREATE TABLE `sessions` (
  `id` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `user_id` bigint unsigned DEFAULT NULL,
  `ip_address` varchar(45) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `user_agent` text COLLATE utf8mb4_unicode_ci,
  `payload` longtext COLLATE utf8mb4_unicode_ci NOT NULL,
  `last_activity` int NOT NULL,
  PRIMARY KEY (`id`),
  KEY `sessions_user_id_index` (`user_id`),
  KEY `sessions_last_activity_index` (`last_activity`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

DROP TABLE IF EXISTS `users`;
CREATE TABLE `users` (
  `id` bigint unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `email_verified_at` timestamp NULL DEFAULT NULL,
  `password` varchar(255) COLLATE utf8mb4_unicode_ci NOT NULL,
  `remember_token` varchar(100) COLLATE utf8mb4_unicode_ci DEFAULT NULL,
  `created_at` timestamp NULL DEFAULT NULL,
  `updated_at` timestamp NULL DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `users_email_unique` (`email`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

INSERT INTO `honey_samples` (`id`, `data`, `created_at`, `updated_at`) VALUES
(1, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 600, \"moisture\": 20.91, \"ph_value\": 3.78, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 05:31:33', '2025-06-21 05:31:33'),
(2, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 700, \"moisture\": 20.91, \"ph_value\": 3.78, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 10:21:14', '2025-06-21 05:31:33'),
(3, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 515.65, \"moisture\": 20.91, \"ph_value\": 3.78, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 10:29:39', '2025-06-21 05:31:33'),
(4, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 515.65, \"moisture\": 20.91, \"ph_value\": 4, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 18:55:39', '2025-06-21 05:31:33'),
(5, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 515.65, \"moisture\": 20.91, \"ph_value\": 6, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 19:15:39', '2025-06-21 05:31:33'),
(6, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 515.65, \"moisture\": 20.91, \"ph_value\": 7, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 19:16:39', '2025-06-21 05:31:33'),
(7, '{\"ambient_reading\": {\"humidity\": 72.43, \"temperature\": 27.01}, \"sensor_readings\": {\"ec_value\": 515.65, \"moisture\": 20.91, \"ph_value\": 8, \"spectroscopy_moisture\": 31.7}, \"absorbance_readings\": {\"blue\": 1.23, \"clear\": 0.0, \"orange\": 0.21, \"near_ir\": 0.32, \"red_ch7\": 0.0, \"red_ch8\": 0.35, \"green_ch4\": 0.77, \"green_ch5\": 0.62, \"violet_ch1\": 0.6, \"violet_ch2\": 1.57}}', '2025-06-21 19:40:39', '2025-06-21 05:31:33');

INSERT INTO `migrations` (`id`, `migration`, `batch`) VALUES
(1, '0001_01_01_000000_create_users_table', 1),
(2, '0001_01_01_000001_create_cache_table', 1),
(3, '0001_01_01_000002_create_jobs_table', 1),
(4, '2025_06_21_043303_add_admin_user', 2),
(5, '2025_06_21_052911_create_honey_samples_table', 3),
(6, '2025_06_21_064308_create_personal_access_tokens_table', 4);

INSERT INTO `users` (`id`, `name`, `email`, `email_verified_at`, `password`, `remember_token`, `created_at`, `updated_at`) VALUES
(1, 'Honey Admin', 'honeyadmin@cvsu.edu.ph', '2025-06-21 04:34:06', '$2y$12$pnHdVupvIqQ7sOLwEEAQbe3zjZQDvnO62SRhKY3XMXMZzz/Upndqi', 'AHejVzGO6XIRnOGT1OHBhMveEXyJeV2kUyyaqW1E802e1regHyGr4P6EJg3m', '2025-06-21 04:34:06', '2025-06-21 04:34:06');



/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;