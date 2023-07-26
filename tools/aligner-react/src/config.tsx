const CONFIG: Config = {
    global_settings: {
        title: "OpenNixie Time Alignment",
    },
    bluetooth_settings: {
        filters: [{ namePrefix: "BT" }, { namePrefix: "JDY" }],
        service: "0000ffe0-0000-1000-8000-00805f9b34fb",
        characteristic: "0000ffe1-0000-1000-8000-00805f9b34fb",
    },
    nixie_settings: {
        cmd: 0xe0,
        ack: 0xe1,
        nack: 0xe2,
        year: 0xf1,
        month: 0xf2,
        day: 0xf3,
        week: 0xf4,
        hour: 0xf5,
        minute: 0xf6,
        second: 0xf7,
    },
};

export interface GlobalConfig {
    title: string;
    [key: string]: any;
}

export interface BluetoothConfig {
    filters: BluetoothLEScanFilter[];
    service: string;
    characteristic: string;
    [key: string]: any;
}

export interface NixieConfig {
    cmd: number;
    ack: number;
    nack: number;
    year: number;
    month: number;
    day: number;
    week: number;
    hour: number;
    minute: number;
    second: number;
    [key: string]: any;
}

export interface Config {
    global_settings: GlobalConfig;
    bluetooth_settings: BluetoothConfig;
    nixie_settings: NixieConfig;
    [key: string]: any;
}

export default CONFIG;
