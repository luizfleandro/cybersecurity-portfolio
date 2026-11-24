# Cybersecurity Portfolio

Write-ups, notes and projects from my path into Blue Team / SOC work.

## Projects in this repository

| Project | What it covers | Skills |
| --- | --- | --- |
| [ESP32 temperature sensor: network security lab](project-es32/) | An ESP32 sends sensor readings to a Python server over plain HTTP and then over HTTPS; the traffic of each version is compared in Wireshark | Networking (DHCP, ARP, TCP), TLS, Wireshark, Python |
| [Fake CAIXA notification investigation](writeups/phishing/caixa-notification/) | Investigation of CAIXA-branded notifications redirecting users to a potentially fraudulent gambling website, documented as a DFIR incident report | Phishing analysis, OSINT, DNS and domain investigation, IOC handling, incident reporting |

## Other security projects

| Repository | What it covers |
| --- | --- |
| [lab-soc-wazuh](https://github.com/luizfleandro/lab-soc-wazuh) | Wazuh SIEM lab with MITRE ATT&CK simulations and AI-assisted alert triage, including prompt injection tests |
| [soc-home-lab](https://github.com/luizfleandro/soc-home-lab) | Docker-based SOC lab with Splunk and Suricata (work in progress) |

## Notes

- Indicators of compromise in the write-ups are defanged (`[.]`, `hxxps`). Do not
  re-enable them outside an isolated analysis environment.
- All offensive activity in these projects was performed only against systems I own,
  in my own lab.
