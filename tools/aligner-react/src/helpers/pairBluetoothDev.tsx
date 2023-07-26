export interface BluetoothDevConfig {
    filters: BluetoothLEScanFilter[];
    service: BluetoothServiceUUID;
    characteristic: BluetoothCharacteristicUUID;
}

export interface BluetoothDev {
    device: BluetoothDevice;
    server?: BluetoothRemoteGATTServer;
    service?: BluetoothRemoteGATTService;
    characteristic?: BluetoothRemoteGATTCharacteristic;
}

const pairBluetoothDev = async (
    bluetoothDeviceConfig: BluetoothDevConfig
): Promise<BluetoothDev> => {
    const {
        filters,
        service: _service,
        characteristic: _characteristic,
    } = bluetoothDeviceConfig;
    const device = await navigator.bluetooth.requestDevice({
        filters: filters,
        optionalServices: [_service],
    });

    const server = await device.gatt?.connect();
    const service = await server?.getPrimaryService(_service);
    const characteristic = await service?.getCharacteristic(_characteristic);
    return { device, server, service, characteristic };
};

export default pairBluetoothDev;
