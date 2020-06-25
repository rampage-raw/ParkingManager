/*
 Navicat Premium Data Transfer

 Source Server         : MySql
 Source Server Type    : MySQL
 Source Server Version : 80016
 Source Host           : localhost:3306
 Source Schema         : parking

 Target Server Type    : MySQL
 Target Server Version : 80016
 File Encoding         : 65001

 Date: 24/06/2020 19:04:56
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for book
-- ----------------------------
DROP TABLE IF EXISTS `book`;
CREATE TABLE `book`  (
  `id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `parkingname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `carpos` int(255) NOT NULL,
  `statime` datetime(0) NULL DEFAULT NULL,
  `endtime` datetime(0) NULL DEFAULT NULL,
  `finish` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ordernum` int(8) NOT NULL,
  PRIMARY KEY (`ordernum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of book
-- ----------------------------
INSERT INTO `book` VALUES ('admin', '九龙湾', 1, '2020-06-22 21:18:00', '2020-06-24 22:19:00', 'yes', 1);
INSERT INTO `book` VALUES ('root', '阳光海天', 1, '2020-06-22 21:19:00', '2020-06-24 21:23:00', 'no', 2);
INSERT INTO `book` VALUES ('haohaoxianshen', '九龙湾', 3, '2020-06-24 14:46:47', '2020-06-26 14:46:46', 'no', 3);
INSERT INTO `book` VALUES ('newone', '阳光海天', 2, '2020-06-24 15:56:20', '2020-06-24 15:58:17', 'no', 4);

-- ----------------------------
-- Table structure for carinfo
-- ----------------------------
DROP TABLE IF EXISTS `carinfo`;
CREATE TABLE `carinfo`  (
  `id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `carid` varchar(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `cartype` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`, `carid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of carinfo
-- ----------------------------
INSERT INTO `carinfo` VALUES ('admin', 'gg123', '小型车');
INSERT INTO `carinfo` VALUES ('haohaoxianshen', 'GTX2080', '大型车');
INSERT INTO `carinfo` VALUES ('newone', 'gtx1070', '中型车');
INSERT INTO `carinfo` VALUES ('root', 'ac12', '小型车');

-- ----------------------------
-- Table structure for consumption
-- ----------------------------
DROP TABLE IF EXISTS `consumption`;
CREATE TABLE `consumption`  (
  `id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `ordernum` int(8) NOT NULL,
  `carpos` int(255) NOT NULL,
  `parkingname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `statime` datetime(6) NULL,
  `endtime` datetime(6) NULL,
  `timeout` int(3) NULL DEFAULT NULL,
  `fare` int(5) NOT NULL,
  PRIMARY KEY (`ordernum`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of consumption
-- ----------------------------
INSERT INTO `consumption` VALUES ('admin', 1, 1, '九龙湾', '2020-06-22 21:18:00.000000', '2020-06-24 22:19:00.000000', 0, 132);

-- ----------------------------
-- Table structure for parkinglot
-- ----------------------------
DROP TABLE IF EXISTS `parkinglot`;
CREATE TABLE `parkinglot`  (
  `parkingname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `posnum` int(5) NOT NULL,
  `emptynum` int(5) NOT NULL,
  `income` bigint(255) NOT NULL,
  `parkingid` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `parkingpassword` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`parkingname`, `parkingid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of parkinglot
-- ----------------------------
INSERT INTO `parkinglot` VALUES ('九龙湾', 3, 2, 132, 'jiulongwan', '123456');
INSERT INTO `parkinglot` VALUES ('阳光海天', 3, 1, 0, 'yangguanhaitian', '123456');

-- ----------------------------
-- Table structure for parkingspace
-- ----------------------------
DROP TABLE IF EXISTS `parkingspace`;
CREATE TABLE `parkingspace`  (
  `carpos` int(255) NOT NULL,
  `parkingname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `carpostype` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `situation` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `statime` datetime(0) NULL DEFAULT NULL,
  `endtime` datetime(0) NULL DEFAULT NULL,
  PRIMARY KEY (`carpos`, `parkingname`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of parkingspace
-- ----------------------------
INSERT INTO `parkingspace` VALUES (1, '九龙湾', '小型车', '空闲', '2020-06-22 21:18:49', '2020-06-24 22:19:08');
INSERT INTO `parkingspace` VALUES (1, '阳光海天', '小型车', '占用', '2020-06-22 21:19:47', '2020-06-24 21:23:36');
INSERT INTO `parkingspace` VALUES (2, '九龙湾', '中型车', '空闲', NULL, NULL);
INSERT INTO `parkingspace` VALUES (2, '阳光海天', '中型车', '占用', '2020-06-24 15:56:20', '2020-06-24 15:58:17');
INSERT INTO `parkingspace` VALUES (3, '九龙湾', '大型车', '占用', '2020-06-24 14:46:47', '2020-06-26 14:46:46');
INSERT INTO `parkingspace` VALUES (3, '阳光海天', '大型车', '空闲', NULL, NULL);

-- ----------------------------
-- Table structure for userinfo
-- ----------------------------
DROP TABLE IF EXISTS `userinfo`;
CREATE TABLE `userinfo`  (
  `id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `tel` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `type` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `balance` int(255) NOT NULL,
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of userinfo
-- ----------------------------
INSERT INTO `userinfo` VALUES ('admin', '朱先生', '12345678911', '普通用户', 200, '123456');
INSERT INTO `userinfo` VALUES ('haohaoxianshen', '沈先生', '17370912404', '年费会员', 10000, 'root');
INSERT INTO `userinfo` VALUES ('newone', '陈先生', '12345434567', '普通用户', 100, '123456');
INSERT INTO `userinfo` VALUES ('root', '王先生', '12345676543', '普通用户', 100, '123456');

SET FOREIGN_KEY_CHECKS = 1;
