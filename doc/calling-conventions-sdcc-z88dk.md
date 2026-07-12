# Comparación de convenciones de llamada en SDCC y z88dk

|                        | __sdcccall(0) | __sdcccall(1) | __z88dk_fastcall |
|------------------------|---------------|---------------|------------------|
| **RETURN**             |               |               |                  |
| 8 bits                 | L             | A             | L                |
| 16 bits                | HL            | DE            | HL               |
| 32 bits                | DE-HL         | HL-DE         | DE-HL            |
| **PARAMETERS**         |               |               |                  |
| 8 bits                 | Stack         | A             | L                |
| 16 bits                | Stack         | HL            | DE               |
| 32 bits                | Stack         | HL-DE         | DE-HL            |
| 8 + 8 bits             | Stack         | A + L         | Invalid          |
| 8 + 16 bits            | Stack         | A + DE        | Invalid          |
| 16 + 8 bits            | Stack         | HL + DE       | Invalid          |
| 16 + 16 bits           | Stack         | HL + Stack    | Invalid          |

---

## 🧩 Descripción

- **__sdcccall(0)** → Convención antigua (por defecto hasta SDCC 4.1.11).  
- **__sdcccall(1)** → Convención nueva (por defecto desde SDCC 4.1.12).  
- **__z88dk_fastcall** → Convención alternativa que solo funciona con funciones de **1 parámetro**.

---

## 📘 Explicación adicional

La nueva convención de llamada maneja más casos que **__z88dk_fastcall**, y también funciona cuando hay más parámetros en la función.  
En esos casos, los parámetros no manejados por los registros se pasan a través del **stack**.

Por ejemplo, si una función toma **3 parámetros de 8 bits**, los dos primeros se pasan por los registros (**A** y **L**) y el tercero por el **stack**.
