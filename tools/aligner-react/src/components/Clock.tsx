import { Component } from "react";

export interface ClockProps {
    label: string;
    value: number;
}

export default class Clock extends Component<ClockProps> {
    render() {
        const { label, value } = this.props;
        return (
            <div className="relative w-48 h-48 lg:w-56 lg:h-56 xl:w-60 xl:h-60 inline-grid place-content-center text-center border-8 border-gray-900 rounded-full">
                <h3 className="font-bold lg:text-lg xl:text-xl flex flex-col gap-1 lg:gap-3">
                    <span className="text-4xl md:text-5xl lg:text-6xl xl:text-7xl">
                        {value}
                    </span>

                    <span>{label.toUpperCase()}</span>
                </h3>
            </div>
        );
    }
}
