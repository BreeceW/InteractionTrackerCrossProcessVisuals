# Cross process visuals with InteractionTracker
This demonstrates [Cross Process Visuals](https://github.com/ahmed605/CompositionSandbox/blob/master/CompositionSandbox.Native/CrossProcessVisuals.h) by Ahmed Walid in the [VirtualSurfaces](https://github.com/microsoft/Windows.UI.Composition-Win32-Samples/tree/master/cpp/VirtualSurfaces) composition sample from Microsoft. The result is two processes are able to display the same visual. One process (the “primary” process) creates a shared visual target and passes it to a new process (the “secondary” process) The secondary process creates the tile grid and handles interactions. It then sets the shared visual target to a [RedirectVisual](https://learn.microsoft.com/en-us/uwp/api/windows.ui.composition.redirectvisual) whose source is the root visual of the tile grid. By using a RedirectVisual and adding it as a VisualInteractionSource of the secondary process’s InteractionTracker, both processes respond to interaction.

## Caveats
* This sample uses internal APIs not meant for general public usage
* RedirectVisual seems to have an issue where the secondary window will not update except where it overlaps the primary window
  * This repo contains a hack/mitigation for that by applying a zero-amount blur over the entire root visual, which forces the whole window to update, but only works when the windows are at least partially overlaid
* Touch/pen manipulation needs to be redirected to InteractionTracker. This sample does not do that for the primary window. I have not yet tested if that is possible, so touch/pen interaction only works in the secondary window. Trackpad interaction works, however.

## Demo
https://github.com/BreeceW/InteractionTrackerCrossProcessVisuals/assets/18747724/3177a0e6-f8a2-4180-afcd-9d3325e90ffc
