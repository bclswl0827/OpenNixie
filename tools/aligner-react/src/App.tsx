import { Component } from "react";
import Container from "./components/Container";
import Clock from "./components/Clock";
import toast, { Toaster } from "react-hot-toast";
import getStructuredTime from "./helpers/getStructuredTime";
import isFeatureSupport from "./helpers/isFeatureSupport";
import pairBluetoothDev, { BluetoothDev } from "./helpers/pairBluetoothDev";
import CONFIG from "./config";

interface AppState {
    hour: number;
    minute: number;
    second: number;
}

export default class App extends Component<{}, AppState> {
    constructor(props: {}) {
        super(props);
        this.state = {
            hour: 0,
            minute: 0,
            second: 0,
        };
    }

    componentDidMount(): void {
        setInterval(this.setStateTime, 1000);
        setTimeout(this.checkCompability, 300);
    }

    setStateTime = (): void => {
        const { hour, minute, second } = getStructuredTime();
        this.setState({ hour, minute, second });
    };

    checkCompability = (): void => {
        if (isFeatureSupport("bluetooth")) {
            toast.success(
                "Your browser support Web Bluetooth, tap the screen to start calibrating."
            );
            window.addEventListener("click", this.pairDevice);
        } else {
            toast.error(
                "Your browser does not support Web Bluetooth, use latest Chrome or Edge."
            );
        }
    };

    pairDevice = async (): Promise<void> => {
        try {
            const res = await pairBluetoothDev(CONFIG.bluetooth_settings);
            toast.success("Device paired successfully, now calibrating.");
            window.removeEventListener("click", this.pairDevice);
            this.setNixieTime(res);
        } catch (err: any) {
            toast.error(err.message);
        }
    };

    setNixieTime = async (dev: BluetoothDev): Promise<void> => {
        try {
            const { characteristic } = dev;
            const { nixie_settings } = CONFIG;

            for (let i in nixie_settings) {
                const buffer = new Uint8Array(3);
                const { year, month, day, week, hour, minute, second } =
                    getStructuredTime();

                buffer[0] = nixie_settings.cmd;
                buffer[1] = nixie_settings[i];
                switch (i) {
                    case "year":
                        buffer[2] = year;
                        break;
                    case "month":
                        buffer[2] = month;
                        break;
                    case "day":
                        buffer[2] = day;
                        break;
                    case "week":
                        buffer[2] = week;
                        break;
                    case "hour":
                        buffer[2] = hour;
                        break;
                    case "minute":
                        buffer[2] = minute;
                        break;
                    case "second":
                        buffer[2] = second;
                        break;
                }

                await characteristic?.writeValue(buffer);
            }

            toast.success("Nixie calibration has completed.");
        } catch (err: any) {
            toast.error(err.message);
        }
    };

    render() {
        const { hour, minute, second } = this.state;
        return (
            <Container>
                <Clock label="hours" value={hour} />
                <Clock label="minutes" value={minute} />
                <Clock label="seconds" value={second} />
                <Toaster />
            </Container>
        );
    }
}
