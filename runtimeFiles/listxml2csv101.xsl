<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:csv="csv:csv">
<xsl:output method="text" encoding="utf-8" />
<xsl:strip-space elements="*" />

    <xsl:variable name="delimiter" select="','" />

<!--last Modified ______ 11:12AM
Purpose:  Used to ____ ,
-->

    <xsl:template match="/">

    <xsl:text>BEGIN SSN </xsl:text> count(<xsl:value-of select="count(ssn)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="LIST"> <xsl:with-param name="match" select="ssn"/>  </xsl:call-template>
    <xsl:text>END SSN&#xa;</xsl:text>

    <xsl:text>BEGIN SSN/P </xsl:text> count(<xsl:value-of select="count(ssn/p)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="LIST"> <xsl:with-param name="match" select="ssn/p"/>  </xsl:call-template>
    <xsl:text>END SSN/P&#xa;</xsl:text>

    <xsl:text>BEGIN SSN/P/V </xsl:text> count(<xsl:value-of select="count(ssn/p/v)"/>)<xsl:text>&#xa;</xsl:text>
    <xsl:call-template name="LIST"> <xsl:with-param name="match" select="ssn/p/v"/></xsl:call-template>
    <xsl:text>END SSN/P/V&#xa;</xsl:text>

  </xsl:template>

    

<xsl:template name="LIST">
    <xsl:param name="match"/>

    <xsl:for-each select="$match">
        <!-- Header -->
        <xsl:if test="position() = 1">

        <xsl:value-of select="concat(name(.),'_id', ',')"/>

        <xsl:for-each select="./@*">
            <xsl:value-of select="name(.)"/><xsl:text>,</xsl:text>
        </xsl:for-each>

        <!-- Parenet ID-->       
        <xsl:value-of select="concat(name(parent::*),'_id', ',')"/>

        <xsl:text>&#xa;</xsl:text>
        </xsl:if>

        <!-- Rows -->
        <xsl:value-of select="position()"/> <xsl:text>,</xsl:text>
        <xsl:for-each select="./@*">
            <xsl:text>"</xsl:text><xsl:value-of select="."/><xsl:text>",</xsl:text>
        </xsl:for-each>
        <!-- Parenet ID-->   
        <xsl:text>"</xsl:text><xsl:value-of select="count(../preceding-sibling::*)+1"/><xsl:text>",</xsl:text>

        <xsl:text>&#xa;</xsl:text>

    </xsl:for-each>
</xsl:template>    

</xsl:stylesheet>
