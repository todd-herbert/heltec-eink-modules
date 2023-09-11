The E-ink modules have an orange "flex-connector", attatching the display to the PCB.
There is some amount of text printed on the connector.

![E-ink module, end-on, displaying flex connector label position](flex_connector.jpg)

The main label, printed on the connector, can be used to [identify the model](/docs/README.md#supported-displays), 
or can be used, as a class name, to declare your panel in your sketch.

To use this label directly as a class name, you should remove all non-alphanumeric characters (no spaces, no dashes, no periods etc.) <br />
For the panel shown above, this class name would be `FPC7525`

```cpp
// Declaration by model
DEPG0154BNS800 display( PIN_DC, PIN_CS, PIN_BUSY );

// Is equivalent to

// Declaration by Flex Connector Label
FPC7525 display( PIN_DC, PIN_CS, PIN_BUSY );
```