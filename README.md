# harb

A **H**eap **A**nalyzer for **R**uby. A tool that can be used to analyze Ruby JSON heap dumps that are generated by `ObjectSpace.dump_all`. Should build on OSX and Linux.

#### Building
`make`, or `DEBUG=1 make` for debugging.

#### Usage
`harb <heap_dump_file>`

#### Example

```
harb (master) $ ./harb heap_dump-1554816045-60.json
parsing (100%)
updating references (100%)
generating dominator tree (100%)
harb> help
You can run the following commands:

              quit - Exits the program
             print - Prints heap info for the address specified
          rootpath - Display the root path for the object specified
              help - Displays this message
           summary - Display a heap dump summary
              diff - Diff current heap dump with specifed dump

harb> print 0x55c02bc2a038
    0x55c02bc2a038: "OBJECT"
             class: TZInfo::TimezoneTransitionDefinition
           memsize: 96
  retained memsize: 96
     references to: [
                      0x55c02bc266b8 (OBJECT: TZInfo::TimezoneOffset)
                      0x55c02bc26690 (OBJECT: TZInfo::TimezoneOffset)
                    ]
   referenced from: [
                      0x55c02bc26758 (ARRAY: size 303)
                    ]

harb> rootpath 0x55c02bc2a038

root path to 0x55c02bc2a038:
                      ROOT (machine_context)
                      0x55bfcfbf0560 (CLASS: RubyVM::InstructionSequence)
                      0x55bfcfc21728 (CLASS: Object)
                      0x55bfd1b1b7c8 (MODULE: TZInfo)
                      0x55bfd0cf5c20 (MODULE: TZInfo::Data)
                      0x55bfd368aa18 (MODULE: TZInfo::Data::Definitions)
                      0x55bfd368a9a0 (MODULE: TZInfo::Data::Definitions::America)
                      0x55c02bc268e8 (MODULE: TZInfo::Data::Definitions::America::St_Johns)
                      0x55c02bc267a8 (OBJECT: TZInfo::TransitionDataTimezoneInfo)
                      0x55c02bc26758 (ARRAY: size 303)
                      0x55c02bc2a038 (OBJECT: TZInfo::TimezoneTransitionDefinition)

harb>
```

#### Dependencies
- libgoogle-perftools-dev
- libcityhash-dev
- libreadline-dev
