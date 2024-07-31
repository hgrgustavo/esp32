CREATE TABLE "Usuario"(
    "id" BIGINT NOT NULL,
    "nome" CHAR(255) NOT NULL,
    "senha" CHAR(255) NOT NULL
);
ALTER TABLE
    "Usuario" ADD PRIMARY KEY("id");
CREATE TABLE "Dispositivos"(
    "id" BIGINT NOT NULL,
    "sensorDistancia" VARCHAR(255) NOT NULL,
    "sensorObstaculo" VARCHAR(255) NOT NULL,
    "miniCamera" VARCHAR(255) NOT NULL,
    "motorVibracao" VARCHAR(255) NOT NULL,
    "altoFalante" VARCHAR(255) NOT NULL,
    "gps" VARCHAR(255) NOT NULL
);
ALTER TABLE
    "Dispositivos" ADD PRIMARY KEY("id");