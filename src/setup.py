def main():
  projectConfigFile = '../.pio/libdeps/heltec_wifi_lora_32/MCCI LoRaWAN LMIC library/project_config/lmic_project_config.h'

  with open(projectConfigFile, 'r') as f:
    data = f.readlines()

  data = [f'// {line}' for line in data]

  with open(projectConfigFile, 'w') as f:
    f.writelines(data)

if __name__ == '__main__':
  main()


