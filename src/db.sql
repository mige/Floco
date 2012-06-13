-- Creator:       MySQL Workbench 5.2.40/ExportSQLite plugin 2009.12.02
-- Author:        Unknown
-- Caption:       New Model
-- Project:       Name of the project
-- Changed:       2012-06-13 20:01
-- Created:       2011-08-31 17:30
PRAGMA foreign_keys = OFF;

-- Schema: mydb
BEGIN;
CREATE TABLE "team_category"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "name" VARCHAR(50) NOT NULL,
  "male" BOOLEAN NOT NULL,
  "max_age" INTEGER NOT NULL
);
CREATE TABLE "camp"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "start_date" DATE NOT NULL,
  "end_date" DATE NOT NULL,
  "place" TINYTEXT NOT NULL,
  "info" TEXT NOT NULL
);
CREATE TABLE "team"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "name" VARCHAR(150) NOT NULL,
  "team_category_id" INTEGER NOT NULL,
  CONSTRAINT "fk_team_team_category1"
    FOREIGN KEY("team_category_id")
    REFERENCES "team_category"("id")
);
CREATE INDEX "team.fk_team_team_category1" ON "team"("team_category_id");
CREATE TABLE "training"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "datetime" DATETIME NOT NULL,
  "place" VARCHAR(150) NOT NULL,
  "canceled" BOOLEAN NOT NULL,
  "team_id" INTEGER NOT NULL,
  CONSTRAINT "fk_training_team1"
    FOREIGN KEY("team_id")
    REFERENCES "team"("id")
);
CREATE INDEX "training.fk_training_team1" ON "training"("team_id");
CREATE TABLE "tournament"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "date" DATE NOT NULL,
  "place" TINYTEXT NOT NULL,
  "season" BOOLEAN NOT NULL,
  "team_id" INTEGER NOT NULL,
  CONSTRAINT "fk_tournament_team1"
    FOREIGN KEY("team_id")
    REFERENCES "team"("id")
);
CREATE INDEX "tournament.fk_tournament_team1" ON "tournament"("team_id");
CREATE TABLE "game"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "time" TIME NOT NULL,
  "note" TEXT NOT NULL,
  "rival" TINYTEXT NOT NULL,
  "tournament_id" INTEGER NOT NULL,
  CONSTRAINT "fk_game_tournament1"
    FOREIGN KEY("tournament_id")
    REFERENCES "tournament"("id")
);
CREATE INDEX "game.fk_game_tournament1" ON "game"("tournament_id");
CREATE TABLE "player"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "firstname" VARCHAR(100) NOT NULL,
  "surname" VARCHAR(100) NOT NULL,
  "birth" DATE NOT NULL,
  "address" VARCHAR(250),
  "email" VARCHAR(150),
  "phone" VARCHAR(13),
  "number" INTEGER NOT NULL,
  "photo" BLOB,
  "post" VARCHAR(50) NOT NULL,
  "team_id" INTEGER,
  CONSTRAINT "fk_player_team1"
    FOREIGN KEY("team_id")
    REFERENCES "team"("id")
);
CREATE INDEX "player.fk_player_team1" ON "player"("team_id");
CREATE TABLE "attendance"(
  "id" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
  "participated" BOOLEAN NOT NULL,
  "player_id" INTEGER NOT NULL,
  "training_id" INTEGER NOT NULL,
  CONSTRAINT "fk_attendance_player1"
    FOREIGN KEY("player_id")
    REFERENCES "player"("id"),
  CONSTRAINT "fk_attendance_training1"
    FOREIGN KEY("training_id")
    REFERENCES "training"("id")
);
CREATE INDEX "attendance.fk_attendance_player1" ON "attendance"("player_id");
CREATE INDEX "attendance.fk_attendance_training1" ON "attendance"("training_id");
CREATE TABLE "camp_has_player"(
  "camp_id" INTEGER NOT NULL,
  "player_id" INTEGER NOT NULL,
  CONSTRAINT "fk_camp_has_player_camp1"
    FOREIGN KEY("camp_id")
    REFERENCES "camp"("id"),
  CONSTRAINT "fk_camp_has_player_player1"
    FOREIGN KEY("player_id")
    REFERENCES "player"("id")
);
CREATE INDEX "camp_has_player.fk_camp_has_player_player1" ON "camp_has_player"("player_id");
CREATE INDEX "camp_has_player.fk_camp_has_player_camp1" ON "camp_has_player"("camp_id");
COMMIT;
