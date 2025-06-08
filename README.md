# 🌱 Green Alert

Green Alert é um aplicativo de monitoramento ambiental inteligente, desenvolvido em ⚛️ React Native com 🚀 Expo, que permite acompanhar sensores ambientais, visualizar alertas, históricos de leituras e gerenciar chamados de atendimento.

---

## 👨‍💻 Desenvolvido por

- **Ana Carolina Reis Santana** — RM: **556219**
- **Leticia Zago** — RM: **558464**
- **Celina Alcantara** — RM: **558090**

---

## 📦 Estrutura do Projeto

```
2TDS-GS2025/
├── app/                  # Aplicativo React Native (Expo)
├── GS-GREEN-ALERT/       # Código ESP32 (PlatformIO)
├── node-red/             # Fluxos Node-RED (opcional)
├── README.md             # Este arquivo
└── ...
```

---

## 🚀 Como Rodar o Projeto

### 1. **Clonar o Repositório**

```bash
git clone https://github.com/prof-atritiack/2TDS-GS2025.git
cd 2TDS-GS2025
```
   ```
2. Inicie o Node-RED:
   ```bash
   node-red
   ```
3. Acesse [http://http://4.201.157.200:1880](http://http://4.201.157.200:1880) e importe o fluxo fornecido.
4. Configure o nó MQTT:
   - Servidor: `4.201.157.200`
   - Porta: `1883`
   - Usuário: `iot`
   - Senha: `Fiap@2tdsvms`
   - Tópico: `sensores/ac`

---
