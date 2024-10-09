/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class YellowRoseAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::FileDragAndDropTarget
{
public:
    YellowRoseAudioProcessorEditor (YellowRoseAudioProcessor&);
    ~YellowRoseAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    bool juce::FileDragAndDropTarget::isInterestedInFileDrag(const juce::StringArray& files);
    void juce::FileDragAndDropTarget::filesDropped(const juce::StringArray& files, int x, int y);

private:
    juce::TextButton mLoadButton{ "Load" };
    std::vector<float> mAudioPoints;
    bool mShouldBePainting{ false };

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    YellowRoseAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YellowRoseAudioProcessorEditor)
};
